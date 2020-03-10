//描点法和画线法绘制镂空三角形

#include <GL/glut.h>
#include<cmath>
/*you may have to change the include to<glut.h> or
elsewhere depending on where it is stored on your system */
/* glut.h usually has included for gl.h and glu.h */

void myinit(void)
{
	/* attributes */
	glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
	glColor3f(1.0, 0.0, 0.0); /* draw in red */
							  /* set up viewing */
	/* 50.0 × 50.0 camera coordinate window with origin lower left */
	glMatrixMode(GL_PROJECTION);	//投影矩阵
	glLoadIdentity();	//矩阵为单位矩阵
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);	//设置绘图区域
	glMatrixMode(GL_MODELVIEW);		//切换到模型视图
}

void LineTra(GLfloat *ver0, GLfloat *ver1, GLfloat *ver2)
{
	if (pow(ver0[0] - ver1[0], 2) + pow(ver0[1] - ver1[1], 2) < 10e-3)
		return;
	glBegin(GL_LINE_LOOP);
	//glVertex2fv(ver0);
	glVertex2fv(ver1);
	glVertex2fv(ver2);
	glEnd();
	float newver0[2],newver1[2],newver2[2];
	newver0[0] = (ver0[0] + ver1[0]) / 2;
	newver0[1] = (ver0[1] + ver1[1]) / 2;
	newver1[0] = (ver1[0] + ver2[0]) / 2;
	newver1[1] = (ver1[1] + ver2[1]) / 2;
	newver2[0] = (ver2[0] + ver0[0]) / 2;
	newver2[1] = (ver2[1] + ver0[1]) / 2;
	LineTra(ver0, newver0, newver2);
	LineTra(ver1, newver0, newver1);
	LineTra(ver2, newver1, newver2);
}

void display(void)
{
	/* A triangle */
	GLfloat vertices[3][2] = { { 0.0,0.0 },{ 25.0,50.0 },{ 50.0,0.0 } };	//最外围的三角形坐标
	int i, j, k;
	int rand();       /* standard random number generator */
	GLfloat p[2] = { 7.5,5.0 };	//初始点
	/* an arbitrary initial point inside traingle */
	glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
	LineTra(vertices[0], vertices[1], vertices[2]);
	//glBegin(GL_POINTS);		//开始绘制点
	///* compute and plots 5000 new points */
	//for (k = 0; k < 358000; k++)
	//{
	//	j = rand() % 3; /* pick a vertex at random *///j为0，1，2
	///* Compute point halfway between selected vertex and old point */
	//	p[0] = (p[0] + vertices[j][0]) / 2.0;
	//	p[1] = (p[1] + vertices[j][1]) / 2.0;

	//	/* plot new point */
	//	glVertex2fv(p);	//以p点坐标绘制点
	//}
	//glEnd();	//结束绘制
	glFlush(); /* clear buffers */
}

void main(int argc, char** argv)
{
	/* Standard GLUT initialization */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /* default, not needed */
	glutInitWindowSize(500, 500); /* 500 × 500 pixel window */
	glutInitWindowPosition(0, 0); /* place window top left on display */
	glutCreateWindow("Sierpinski Gasket"); /* window title */
	glutDisplayFunc(display);
	/* display callback invoked when window opened */
	myinit(); /* set attributes */
	glutMainLoop(); /* enter event loop */
}