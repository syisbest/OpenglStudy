//�����α任����һ��д��������������

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
 /* ��ʼ����ʾ���ڴ�С */
GLsizei winWidth = 600, winHeight = 600;
/* ������������ϵ����ʾ��Χ */
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;
/* �����ά�����ݽṹ */
class wcPt2D
{
public:
	GLfloat x, y;
};
typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;   //���帴�Ͼ���
const GLdouble pi = 3.14159;
void init(void)
{ /* ������ʾ���ڵı�����ɫΪ��ɫ */
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
/* ����3*3�ĵ�λ���� */
void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	GLint row, col;
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matIdent3x3[row][col] = (row == col);//�������Ϊ1
}
/* �任����m1ǰ�˾���m2,��������m2�� */
void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row, col;
	Matrix3x3 matTemp;
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matTemp[row][col] = m1[row][0] * m2[0][col]
			+ m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
	//�˵Ľ������matTemp��ٴ���m2
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			m2[row][col] = matTemp[row][col];
}
/* ƽ�Ʊ任������ƽ����tx��ty */
void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTransl;
	/* ��ʼ��ƽ�ƾ���Ϊ��λ���� */
	matrix3x3SetIdentity(matTransl);
	matTransl[0][2] = tx;
	matTransl[1][2] = ty;
	/* ��ƽ�ƾ���ǰ�˵����Ͼ���matComposite�� */
	matrix3x3PreMultiply(matTransl, matComposite);
}
/* ��ת�任����������Ϊ���ĵ�pivotPt����ת�Ƕ�theta */
void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
	Matrix3x3 matRot;
	/* ��ʼ����ת����Ϊ��λ���� */
	matrix3x3SetIdentity(matRot);
	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = pivotPt.x*(1 - cos(theta)) + pivotPt.y*sin(theta);
	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = pivotPt.y*(1 - cos(theta)) - pivotPt.x*sin(theta);
	/* ����ת����ǰ�˵����Ͼ���matComposite�� */
	matrix3x3PreMultiply(matRot, matComposite);
}
/* �����任����������Ϊ��׼��fixedPt�����ű���sx��sy */
void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
	Matrix3x3 matScale;
	/* ��ʼ�����ž���Ϊ��λ���� */
	matrix3x3SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx)*fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy)*fixedPt.y;
	/* �����ž���ǰ�˵����Ͼ���matComposite�� */
	matrix3x3PreMultiply(matScale, matComposite);
}
/* ���ø��Ͼ������任������ */
void transformVerts2D(GLint nVerts, wcPt2D * verts)
{
	GLint k;
	GLfloat temp;
	for (k = 0; k < nVerts; k++)
	{
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x
			+ matComposite[1][1] * verts[k].y + matComposite[1][2];
		verts[k].x = temp;
	}
}
/* �����λ��ƺ��� */
void triangle(wcPt2D * verts)
{
	GLint k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)  glVertex2f(verts[k].x, verts[k].y);
	glEnd();
}
void displayFcn(void)
{
	/* ���������εĳ�ʼλ�� */
	GLint nVerts = 3;
	wcPt2D verts[3] = { { 50.0,25.0 },{ 150.0,25.0 },{ 100.0,100.0 } };
	/* ��������������λ�� */
	wcPt2D centroidPt;
	GLint k, xSum = 0, ySum = 0;
	for (k = 0; k < nVerts; k++)
	{
		xSum += verts[k].x;
		ySum += verts[k].y;
	}
	centroidPt.x = GLfloat(xSum) / GLfloat(nVerts);
	centroidPt.y = GLfloat(ySum) / GLfloat(nVerts);
	/* ���ü��α任����*/
	wcPt2D pivPt, fixedPt;
	pivPt = centroidPt;//�������е�
	fixedPt = centroidPt;
	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 0.5, sy = 0.5;
	GLdouble theta = pi / 2.0;//��ת90��
	glClear(GL_COLOR_BUFFER_BIT); // �����ʾ����
	glColor3f(0.0, 0.0, 1.0); // ����ǰ��ɫΪ��ɫ
	triangle(verts); //��ʾ��ɫ�����Σ��任ǰ��
	/* ��ʼ�����Ͼ���Ϊ��λ���� */
	matrix3x3SetIdentity(matComposite);
	/* ���ݱ任�����ؽ����Ͼ��� */
	scale2D(sx, sy, fixedPt); //�任����1:���ű任
	rotate2D(pivPt, theta); //�任����2:��ת�任
	translate2D(tx, ty); //�任����3:ƽ�Ʊ任
	/* Ӧ�ø��Ͼ��������� */
	transformVerts2D(nVerts, verts);
	glColor3f(1.0, 0.0, 0.0); //��������ǰ��ɫΪ��ɫ
	triangle(verts); //��ʾ��ɫ�����Σ��任��
	glFlush();
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰ���� 
	glLoadIdentity(); //����ǰ��������Ϊ��λ���� 
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	//�����ά��ͶӰ���� 
	glClear(GL_COLOR_BUFFER_BIT); //�����ǰ��д����ɫ���� 
}
void main(int argc, char ** argv)
{
	glutInit(&argc, argv);  // ��ʼ��GLUT�� 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//�����壬����RGBģʽ���� 
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("��ά���α任ʵ��-���ϱ任");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}
