//ɨ�����㷨�������

#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
using namespace std;

class MapPoint
{
public:
	double longitude;
	double latitude;
};
class Polygona
{
public:
	vector<MapPoint> points;  //����εĶ������� 
};
vector<Polygona *> polys;   //����μ���
vector <Polygona *> ReadMapData(const char* filename)	//���ļ��ж������е㲢��ֵ���ݸ�һ������μ���
{
	int PointCount;
	vector <Polygona*> polygonas;	//����μ���
	ifstream fs(filename);    //��ָ��·���ж�ȡdouble���͵�����
	while (fs.eof() != true)	//һֱ��ȡ���룬ֱ���������
	{
		Polygona* poly = new Polygona;	//��ļ���
		fs >> PointCount;	//��һ��ֵ��ֵ��PointCount����Ϊ��ĸ���
		cout << PointCount << endl;	//������ֵ
		for (int i = 0; i < PointCount; i++)	//�������PointCount������
		{
			MapPoint p;	//��p
			fs >> p.longitude >> p.latitude;	//����ľ�γ
			poly->points.push_back(p);    //��β������һ�����ݣ��Ѷ������ĵ㸳ֵ��poly��points
		}
		polygonas.push_back(poly);	//��poly��ֵ��polygonas

	}
	return polygonas;
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);    //����ɫɫ���Ƹ�ʡ�߽�
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_BACK, GL_LINE);	//���÷���Ϊ����
	for (int i = 0; i < polys.size(); i++)
	{
		vector<MapPoint> points = polys[i]->points;	//��polys����õ����е�points
		glBegin(GL_LINE_LOOP);	//��ʼ����ֱ��
		for (int j = 0; j < points.size(); j++)
		{
			glVertex3f(points[j].longitude, points[j].latitude, 0.0);	//x��y����
		}
		glEnd();
	}
	glFlush();
}
void init(void)
{
	//���ñ�����ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//��ʼ���۲�ֵ
	glMatrixMode(GL_PROJECTION);    //������ģʽ��ΪͶӰ
	glLoadIdentity();                 //�Ծ�����е�λ��
	glOrtho(110.0, 118.0, 30.0, 38.0, -1.0, 1.0);   //����ƽ��ͶӰ����
}
int main(int argc, char** argv)
{
	// �����ļ�Ŀ¼
	const char *filename = "E:/���ϵ�ͼ��γ������.txt";
	polys = ReadMapData(filename);	//���ļ��ж�ȡ������洢��polys��
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//�������RGB
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("��ͼ����");
	init();
	glutDisplayFunc(display);     //��ʾ�ص�����
	glutMainLoop();
	return 0;
}

#include<windows.h>
#include<GL/glut.h>
const int POINTNUM = 5;      //����ε���.

/******����ṹ�����ڻ��Ա߱�AET���±߱�NET***********************************/
typedef struct XET
{
	float x;
	float dx, ymax;
	XET* next;
} AET, NET;

/******�����ṹ��point******************************************************/
struct point
{
	float x;
	float y;
} polypoint[POINTNUM] = { {400,200},{1300,200},{1500,500},{1000,1100},{200,700} }; //����ζ���

void PolyScan()
{
	/******������ߵ��y����(ɨ�赽�˽���)****************************************/
	int MaxY = 0;
	int i;
	for (i = 0; i < POINTNUM; i++)
		if (polypoint[i].y > MaxY)
			MaxY = polypoint[i].y;


	/******��ʼ��NET��************************************************************/
	NET *pNET[1200];
	for (i = 0; i <= MaxY; i++)
	{
		pNET[i] = new NET;
		pNET[i]->next = nullptr;
	}
	/******ɨ�貢����NET��*********************************************************/
	for (i = 0; i <= MaxY; i++)
	{
		for (int j = 0; j < POINTNUM; j++)
			if (polypoint[j].y == i)
			{
				//һ�����ǰ���һ�����γ�һ���߶Σ�������ĵ�Ҳ�γ��߶�
				if (polypoint[(j - 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
				{
					NET *p = new NET;
					p->x = polypoint[j].x;
					p->ymax = polypoint[(j - 1 + POINTNUM) % POINTNUM].y;
					p->dx = (polypoint[(j - 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j - 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
				if (polypoint[(j + 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
				{
					NET *p = new NET;
					p->x = polypoint[j].x;
					p->ymax = polypoint[(j + 1 + POINTNUM) % POINTNUM].y;
					p->dx = (polypoint[(j + 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j + 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
	}

	/*******��ʼ��AET��***********************************************************/
	AET *pAET = new AET;
	pAET->next = nullptr;
	/******���������»��Ա߱�AET*****************************************************/
	for (i = 0; i <= MaxY; i++)
	{
		//�����µĽ���x,����AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//���º���AET������*************************************************************/
		//�ϱ�����,���ٿ��ٿռ�
		AET *tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p)
		{
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			NET *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}
		//(�Ľ��㷨)�ȴ�AET����ɾ��ymax==i�Ľ��****************************************/
		AET *q = pAET;
		p = q->next;
		while (p)
		{
			if (p->ymax == i)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}
		//��NET�е��µ����AET,���ò��뷨��Xֵ��������**********************************/
		p = pNET[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;
			NET *s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		/******��������ɫ***************************************************************/
		glClear(GL_COLOR_BUFFER_BIT);        //��ֵ�Ĵ�����ʾ.
		glColor3f(0.0, 0.0, 0.0);             //����ֱ�ߵ���ɫ��ɫ
		glBegin(GL_POINTS);
		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i(static_cast<int>(j), i);
			p = p->next->next;//���Ƕ˵����
		}
	}
	glEnd();
	glFlush();
}

void init(int argc, char** argv)
{
	glutInit(&argc, argv);  //I��ʼ�� GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //������ʾģʽ�����������ʹ��RGBģ��
	glutInitWindowPosition(50, 100);  //���ô��ڵĶ��������λ��
	glutInitWindowSize(800, 600);  //���ô��ڵĸ߶ȺͿ��
	glutCreateWindow("Test");

	glClearColor(1.0, 1.0, 1.0, 0); //���ڱ�����ɫΪ��ɫ
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1800, 0, 1200);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	glPointSize(1);
	glBegin(GL_POINTS);
	PolyScan();
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	init(argc, argv);
	glutDisplayFunc(myDisplay);        //ͼ�εĶ��崫�ݸ���window.
	glutMainLoop();
	return 0;
}
