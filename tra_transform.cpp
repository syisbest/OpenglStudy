//������˼��㸴�ϱ任���󣬻�����תƽ��������

#include <iostream>
#include <GL/glut.h>
#include<cmath>
using namespace std;

class Point
{
public:
	float x;
	float y;
};
class Trangle
{
public:
	Point A;
	Point B;
	Point C;
};
float conMatri[3][3],traMatri[3][3];
const float pi = 3.1415926;
void FirstTrangle(Trangle *trangle)//A(1,2)��B(6,2)��C(3,6)
{
	trangle->A.x = 1;
	trangle->A.y = 2;
	trangle->B.x = 6;
	trangle->B.y = 2;
	trangle->C.x = 3;
	trangle->C.y = 6;
}
void tra2to3Matri(Trangle *tra)//�����������Ϊ��ά
{
	traMatri[0][0] = tra->A.x;
	traMatri[1][0] = tra->A.y;
	traMatri[2][0] = 1;
	traMatri[0][1] = tra->B.x;
	traMatri[1][1] = tra->B.y;
	traMatri[2][1] = 1;
	traMatri[0][2] = tra->C.x;
	traMatri[1][2] = tra->C.y;
	traMatri[2][2] = 1;
}
void RotMatri(float theta,Point point)//��ת�任����ĳһ��
{
	conMatri[0][0] = cos(theta);
	conMatri[0][1] = -sin(theta);
	conMatri[0][2] = point.x*(1 - cos(theta)) + point.y*sin(theta);
	conMatri[1][0] = sin(theta);
	conMatri[1][1] = cos(theta);
	conMatri[1][2] = point.y*(1 - cos(theta)) - point.x*sin(theta);
	conMatri[2][0] = 0;
	conMatri[2][1] = 0;
	conMatri[2][2] = 1;
}
void MoveMatri(float x, float y)//ƽ�Ʊ任
{
	conMatri[0][0] = 1;
	conMatri[0][1] = 0;
	conMatri[0][2] = x;
	conMatri[1][0] = 0;
	conMatri[1][1] = 1;
	conMatri[1][2] = y;
	conMatri[2][0] = 0;
	conMatri[2][1] = 0;
	conMatri[2][2] = 1;
}
void recombination()//���ϱ任
{
	//Point midpoint;
	//float sum = 0;
	//for (int i = 0; i < 3; i++)
	//	sum += traMatri[0][i];
	//midpoint.x = sum / 3.0;
	//for (int i = 0; i < 3; i++)
	//	sum += traMatri[1][i];
	//midpoint.y = sum / 3.0;
	//RotMatri(60 * pi / 180, midpoint);//���������е�
	Point oripoint;
	oripoint.x = oripoint.y = 0;
	RotMatri(60 * pi / 180, oripoint);//��ԭ��
	float firstMatri[3][3] = {0};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			firstMatri[i][j] =	conMatri[i][j];
	MoveMatri(2, -1);
	float secondMatri[3][3] = {0};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			secondMatri[i][j] = conMatri[i][j];
	float thirdMatri[3][3] = {0};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				thirdMatri[i][j] += secondMatri[i][k] * firstMatri[k][j];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			conMatri[i][j] = thirdMatri[i][j];
}
void CalTraMatri()//�������
{
	float newmatri[3][3] = {0};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				newmatri[i][j] += conMatri[i][k] * traMatri[k][j];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			traMatri[i][j] = newmatri[i][j];
}
void ConverTra()//�仯֮��Ľ��
{
	recombination();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << conMatri[i][j] << " ";
		cout << endl;
	}
		
	CalTraMatri();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << traMatri[i][j] << " ";
		cout << endl;
	}
}
void myinit(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //������ɫ
	glColor3f(1.0, 0.0, 0.0); //��ɫ
	glMatrixMode(GL_PROJECTION);	//ͶӰ����
	glLoadIdentity();	//����Ϊ��λ����
	gluOrtho2D(-3.0, 12.0, -3.0, 12.0);	//���û�ͼ����
	glMatrixMode(GL_MODELVIEW);		//�л���ģ����ͼ
}
void myDisplay(void)	//��ͼ����
{
	Trangle *trangle = new Trangle;
	FirstTrangle(trangle);
	tra2to3Matri(trangle);
	glBegin(GL_TRIANGLES);	//��ʼ���������ͣ��任ǰ��
	//�����͵�����������
	glVertex2f(traMatri[0][0],traMatri[1][0]);	
	glVertex2f(traMatri[0][1], traMatri[1][1]);
	glVertex2f(traMatri[0][2], traMatri[1][2]);
	glEnd();	//��������
	ConverTra();
	glBegin(GL_TRIANGLES);	//��ʼ���������ͣ��任��
	glVertex2f(traMatri[0][0], traMatri[1][0]);
	glVertex2f(traMatri[0][1], traMatri[1][1]);
	glVertex2f(traMatri[0][2], traMatri[1][2]);
	glEnd();	//��������
	glFlush(); // ǿ��ˢ��
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);//��ʼ��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //��ͼģʽ
	glutInitWindowSize(500, 500); //���ڴ�С
	glutInitWindowPosition(0, 0); //λ��
	glutCreateWindow("�任������"); //����
	myinit(); //��ʼ��
	glutDisplayFunc(myDisplay);//��ʼ��ͼ
	glutMainLoop(); //��ʼѭ��
	return 0;
}