//绘制四面体
#include <GL/glut.h>
#include<iostream>
using namespace std;
float angle;


GLfloat points0[4][3] = { {0,1,0},{ -sqrtf(3) / 2,-1.0f / 2.0f,0 },{sqrtf(3) / 2,-1.0f / 2.0f,0 },{0,0,sqrtf(2)} };
GLfloat Colors0[4][3] = { {1,0,0},{0,1,0},{0,0,1} ,{0,1,1} }; //四面体的颜色
int vertice0[4][3] = { { 0,1,2 },{ 0,2,3 },{0,3,1},{1,2,3} };
//四面体的顶点号序列
void initGL(GLvoid)
{
	glShadeModel(GL_SMOOTH); //设置着色模式,多边形内部区域的颜色将根据所有顶点的颜色差值得到。
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置当前帧的背景颜色 
	glClearDepth(1.0f);  // 设置深度缓存
	glEnable(GL_DEPTH_TEST); // 检查当前像素前面是否有别的像素，如果别的像素挡到它，那它就不会绘制
	glDepthFunc(GL_LEQUAL); //如果输入的深度值小于或等于参考值，通过
	glEnable(GL_COLOR_MATERIAL); // 使用颜色材质,可用颜色来贴物体
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//告诉OpenGL希望进行最好的透视修正
}
void CreateTetrahedron()
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; i++)
	{
		glColor3fv(Colors0[i]);
		for (int j = 0; j < 3; j++)
		{
			int VtxId = vertice0[i][j];
			glVertex3fv(points0[VtxId]);
		}
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 清空显示窗口
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);//平移至下方便于观察
	glRotatef(angle, 0.0f, 1.0f, 0.0f); //旋转一个角度
	CreateTetrahedron();  //创建四面体
	glPopMatrix();

	angle += 0.01f;  //修改四面体的旋转角度
	glutSwapBuffers();
}
void reshape(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height,
		0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Tetrahedron");
	initGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
}
