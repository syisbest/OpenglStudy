//���Ƽ�ͼ�Σ��������������κ͵�

#include <GL/glut.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#define BUFFER_OFFSET(x)  ((const void*) (x))

void myDisplay(void)	//��ͼ����
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	//���ñ�����ɫ0,0,0,0Ϊ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);  //�����ɫ����
	glColor3f(1.0f, 1.0f, 1.0f); //���õ�ǰ֡�ı�����ɫ
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);	//����һ��������
	float a[2][2];
	a[0][0] = 0;
	a[0][1] = 1;
	a[1][0] = 0.8;
	a[1][1] = -0.5;
	glBegin(GL_TRIANGLES);	//��ʼ����������
	//�����͵�����������������ǵ���ɫ
	glColor3f(1.0f, 0.0f, 0.0f);  glVertex2fv(a[0]);	
	glColor3f(0.0f, 1.0f, 0.0f);  glVertex2fv(a[1]);
	glColor3f(0.0f, 0.0f, 1.0f);  glVertex2f(-0.8f, -0.5f);
	glEnd();	//��������

	glPointSize(3);	//���õ�Ĵ�С
	glBegin(GL_POINTS);	//��ʼ���Ƶ�
	//���������㣬��ɫ������
	glColor3f(1.0f, 0.0f, 0.0f);  glVertex2f(-0.4f, -0.4f);
	glColor3f(0.0f, 1.0f, 0.0f);  glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);  glVertex2f(0.4f, 0.4f);
	glEnd();	//��������

	glFlush(); // ǿ��ˢ��
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);	//��ʼ��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//���ó�ʼ��ʾģʽ
	glutInitWindowPosition(100, 100);	//��ʼ����λ��
	glutInitWindowSize(400, 400);	//��ʼ���ڴ�С
	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Hello World");	//��������
	//glewExperimental = GL_TRUE;

	/* if (glewInit()) {
	cerr << "Unable to initialize GLEW ... exiting" << endl;
	exit(EXIT_FAILURE);
	}*/
	glutDisplayFunc(&myDisplay);	//ע���ͼ����
	glutMainLoop();		//��ʼѭ��
	return 0;
}
