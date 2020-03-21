//正方体的三视图

#include <GL/glut.h>
#include <iostream>
using namespace std;

int cube[8][4] = { {0,0,0,1},{0,0,100,1},{100,0,100,1},{100,100,100,1},{0,100,100,1},{100,0,0,1},{100,100,0,1},{0,100,0,1} };
int my_cube[4][8] = { {0,100,100,0,0,100,100,0},
						{0,0,100,100,0,0,100,100},
						{100,100,100,100,0,0,0,0},
						{1,1,1,1,1,1,1,1} };
int new_cube1[4][8];
int new_cube2[4][8];
int new_cube3[4][8];
void three_vision()
{
	int front_view[4][4] = { {1,0,0,0},{0,0,0,0},{0,0,1,0},{0,0,0,1} };
	int planform[4][4] = { {1,0,0,0},{0,0,0,0},{0,-1,0,-50},{0,0,0,1} };
	int side_view[4][4] = { {0,-1,0,-50},{0,0,0,0},{0,0,1,0},{0,0,0,1} };
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				new_cube1[i][j] += front_view[i][k] * my_cube[k][j];
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				new_cube2[i][j] += planform[i][k] * my_cube[k][j];
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				new_cube3[i][j] += side_view[i][k] * my_cube[k][j];
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << new_cube1[i][j]<<"\t";
		}
		cout << endl;
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << new_cube2[i][j] << "\t";
		}
		cout << endl;
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << new_cube3[i][j] << "\t";
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

	glBegin(GL_LINES);
	glVertex2d(-200, 0);
	glVertex2d(200, 0);
	glVertex2d(0, -200);
	glVertex2d(0, 200);
	glEnd();	//结束绘制
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(new_cube1[0][0], new_cube1[2][0]);
	glVertex2d(-new_cube1[0][1], new_cube1[2][1]);
	glVertex2d(-new_cube1[0][5], new_cube1[2][5]);
	glVertex2d(new_cube1[0][4], new_cube1[2][4]);
	glEnd();	//结束绘制
	glBegin(GL_LINE_LOOP);
	glVertex2d(new_cube2[0][0], new_cube2[2][0]);
	glVertex2d(-new_cube2[0][1], new_cube2[2][1]);
	glVertex2d(-new_cube2[0][2], new_cube2[2][2]);
	glVertex2d(new_cube2[0][3], new_cube2[2][3]);
	glEnd();	//结束绘制
	glBegin(GL_LINE_LOOP);
	glVertex2d(-new_cube3[0][0], new_cube3[2][0]);
	glVertex2d(-new_cube3[0][2], new_cube3[2][2]);
	glVertex2d(-new_cube3[0][6], new_cube3[2][6]);
	glVertex2d(-new_cube3[0][4], new_cube3[2][4]);
	glEnd();	//结束绘制

	glFlush(); // 强制刷新
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("三视图");
	three_vision();
	glutDisplayFunc(display);//开始绘图
	glutMainLoop(); //开始循环
}
