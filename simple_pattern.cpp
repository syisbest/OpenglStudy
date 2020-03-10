//绘制简单图形，如三角形正方形和点

#include <GL/glut.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#define BUFFER_OFFSET(x)  ((const void*) (x))

void myDisplay(void)	//绘图函数
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	//设置背景颜色0,0,0,0为黑色
	glClear(GL_COLOR_BUFFER_BIT);  //清除颜色缓冲
	glColor3f(1.0f, 1.0f, 1.0f); //设置当前帧的背景颜色
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);	//绘制一个正方形
	float a[2][2];
	a[0][0] = 0;
	a[0][1] = 1;
	a[1][0] = 0.8;
	a[1][1] = -0.5;
	glBegin(GL_TRIANGLES);	//开始绘制三角型
	//三角型的三个点坐标和三个角的颜色
	glColor3f(1.0f, 0.0f, 0.0f);  glVertex2fv(a[0]);	
	glColor3f(0.0f, 1.0f, 0.0f);  glVertex2fv(a[1]);
	glColor3f(0.0f, 0.0f, 1.0f);  glVertex2f(-0.8f, -0.5f);
	glEnd();	//结束绘制

	glPointSize(3);	//设置点的大小
	glBegin(GL_POINTS);	//开始绘制点
	//绘制三个点，颜色和坐标
	glColor3f(1.0f, 0.0f, 0.0f);  glVertex2f(-0.4f, -0.4f);
	glColor3f(0.0f, 1.0f, 0.0f);  glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);  glVertex2f(0.4f, 0.4f);
	glEnd();	//结束绘制

	glFlush(); // 强制刷新
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);	//初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//设置初始显示模式
	glutInitWindowPosition(100, 100);	//初始窗口位置
	glutInitWindowSize(400, 400);	//初始窗口大小
	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Hello World");	//窗口名称
	//glewExperimental = GL_TRUE;

	/* if (glewInit()) {
	cerr << "Unable to initialize GLEW ... exiting" << endl;
	exit(EXIT_FAILURE);
	}*/
	glutDisplayFunc(&myDisplay);	//注册绘图函数
	glutMainLoop();		//开始循环
	return 0;
}
