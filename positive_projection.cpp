//正方体的正轴测图

#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
const float pi = 3.1415926;

int cube[8][4] = { {0,0,0,1},{0,0,100,1},{100,0,100,1},{100,100,100,1},{0,100,100,1},{100,0,0,1},{100,100,0,1},{0,100,0,1} };
float my_cube[4][8] = { {0,100,100,0,0,100,100,0},
						{0,0,100,100,0,0,100,100},
						{100,100,100,100,0,0,0,0},
						{1,1,1,1,1,1,1,1} };
float new_cube1[4][8];
void projection()
{
	float theta = 20.42f * pi / 180;
	float fai = 19.28f*pi / 180;
	//theta=45,fai=35.16是正等测
	//theta=20.42,fai=19.28是正二测
	
	float t[4][4] = { {cos(theta),-sin(theta),0,0},{0,0,0,0},{-sin(theta)*sin(fai),-cos(theta)*sin(fai),cos(fai),0},{0,0,0,1} };
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				new_cube1[i][j] += t[i][k] * my_cube[k][j];
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << new_cube1[i][j] << "\t\t";
		}
		cout << endl;
	}
}
void display(void)	//绘图函数
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景白色
	glClear(GL_COLOR_BUFFER_BIT);  //清除颜色缓冲
	glColor3f(1.0, 0.0, 0.0); //红色
	glMatrixMode(GL_PROJECTION);	//投影矩阵
	glLoadIdentity();	//矩阵为单位矩阵
	gluOrtho2D(-200.0, 200.0, -200.0, 200.0);	//设置绘图区域
	glMatrixMode(GL_MODELVIEW);		//切换到模型视图
	const float theta = 120.0f * pi / 180.0f;
	glBegin(GL_LINES);
	glVertex2d(0, 0);
	glVertex2d(0, 200);
	glVertex2d(0, 0);
	glVertex2d(-200*sin(theta), 200*cos(theta));
	glVertex2d(0, 0);
	glVertex2d(200*sin(theta), 200*cos(theta));
	glEnd();	//结束绘制
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(new_cube1[0][0], new_cube1[2][0]);
	glVertex2f(new_cube1[0][1], new_cube1[2][1]);
	glVertex2f(new_cube1[0][2], new_cube1[2][2]);
	glVertex2f(new_cube1[0][3], new_cube1[2][3]);
	glEnd();	//结束绘制
	glBegin(GL_LINE_LOOP);
	glVertex2f(new_cube1[0][4], new_cube1[2][4]);
	glVertex2f(new_cube1[0][5], new_cube1[2][5]);
	glVertex2f(new_cube1[0][6], new_cube1[2][6]);
	glVertex2f(new_cube1[0][7], new_cube1[2][7]);
	glEnd();	//结束绘制
	glBegin(GL_LINES);
	for (int i = 0; i < 4; ++i)
	{
		glVertex2f(new_cube1[0][i], new_cube1[2][i]);
		glVertex2f(new_cube1[0][i+4], new_cube1[2][i+4]);
	}
	glEnd();	//结束绘制
	glFlush(); // 强制刷新
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("正二测");
	projection();
	glutDisplayFunc(display);//开始绘图
	glutMainLoop(); //开始循环
}
