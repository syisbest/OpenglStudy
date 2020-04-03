//二次B样条曲线
#include <math.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

#define NUM_POINTS 3
#define NUM_SEGMENTS (NUM_POINTS-2)  

struct Point2
{
	double x;
	double y;

	Point2() { ; }
	Point2(int px, int py) { x = px; y = py; }
	void SetPoint2(int px, int py) { x = px; y = py; }
};

/*全局变量*/
Point2 vec[NUM_POINTS];

/*绘制B样条曲线*/
void Bspline(int n)
{
	float f1, f2, f3;
	float deltaT = 1.0 / n;
	float T;

	glBegin(GL_LINE_STRIP);
	for (int num = 0; num < NUM_SEGMENTS; num++)
	{
		for (int i = 0; i <= n; i++) {

			T = i * deltaT;

			f1 = (T*T - 2 * T + 1) / 2.0;
			f2 = (-2 * T*T + 2 * T + 1) / 2.0;
			f3 = T * T / 2.0;

			glVertex2f(f1*vec[num].x + f2 * vec[num + 1].x + f3 * vec[num + 2].x,
				f1*vec[num].y + f2 * vec[num + 1].y + f3 * vec[num + 2].y);
		}
	}

	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glLineWidth(1.5f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < NUM_POINTS; i++)
	{
		glVertex2f(vec[i].x, vec[i].y);
	}
	glEnd();

	glPointSize(5.0f);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < NUM_POINTS; i++)
	{
		glVertex2f(vec[i].x, vec[i].y);
	}
	glVertex2f(3, 3);
	glVertex2f(4.125, 4.25);
	glVertex2f(5.5, 4);
	glEnd();

	Bspline(20);

	glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);

	vec[0].SetPoint2(2, 1);
	vec[1].SetPoint2(4, 5);
	vec[2].SetPoint2(7, 3);
}
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0, 10.0, 0.0*(GLfloat)h / (GLfloat)w, 10.0*(GLfloat)h / (GLfloat)w, 0.0, 10.0);
    else
        glOrtho(0.0*(GLfloat)w / (GLfloat)h, 10.0*(GLfloat)w / (GLfloat)h, 0.0, 10.0, 0.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("二次B样条曲线");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;

}