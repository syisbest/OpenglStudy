//二或三次Bezier曲线
#include <GL/glut.h>
GLfloat ctrlpoints[4][3] =
{ { -4.5, -4.0, 0.0}, { -3.0, 2.5, 0.0 },{2.0, 4.5, 0.0}, { 2.0, -3.0, 0.0 } };
GLfloat test[3][3] = { {2,1,0},{4,5,0},{7,3,0} };

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	//下行用于定义曲线函数
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &test[0][0]);//order为点的个数，即4个点求三次，3个点求二次
	glEnable(GL_MAP1_VERTEX_3); //将当前曲线函数激活
}
void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	//下面用求值器按20等分计算Bezier曲线上的点
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 20; i++)
		glEvalCoord1f((GLfloat)i / 20.0);  //相当于调用了glVertex*()
	glEnd();
	//描点
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
	for (int i = 0; i < 3; ++i)
	{
		glVertex3fv(&test[i][0]);
	}
	glEnd();
	//glBegin(GL_POINTS);
	//glColor3f(1.0, 0.0, 1.0);
	//glVertex3f(4.25,3.5,0);
	//glEnd();
	//下面绘制控制多边形
	glLineWidth(1);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 3; i++)
		glVertex3fv(&test[i][0]);
		//glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0*(GLfloat)h / (GLfloat)w, 10.0*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0*(GLfloat)w / (GLfloat)h, 10.0*(GLfloat)w / (GLfloat)h, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("二次Bezier曲线");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
