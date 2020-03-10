//扫描线算法画五边形

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
	vector<MapPoint> points;  //多边形的顶点序列 
};
vector<Polygona *> polys;   //多边形集合
vector <Polygona *> ReadMapData(const char* filename)	//从文件中读出所有点并把值传递给一个多边形集合
{
	int PointCount;
	vector <Polygona*> polygonas;	//多边形集合
	ifstream fs(filename);    //从指定路径中读取double类型的数据
	while (fs.eof() != true)	//一直读取输入，直到输入结束
	{
		Polygona* poly = new Polygona;	//点的集合
		fs >> PointCount;	//读一个值赋值给PointCount，即为点的个数
		cout << PointCount << endl;	//输出这个值
		for (int i = 0; i < PointCount; i++)	//往后面读PointCount个坐标
		{
			MapPoint p;	//点p
			fs >> p.longitude >> p.latitude;	//读点的经纬
			poly->points.push_back(p);    //在尾部加入一个数据，把读出来的点赋值到poly的points
		}
		polygonas.push_back(poly);	//把poly赋值给polygonas

	}
	return polygonas;
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);    //用蓝色色绘制各省边界
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_BACK, GL_LINE);	//设置反面为线形
	for (int i = 0; i < polys.size(); i++)
	{
		vector<MapPoint> points = polys[i]->points;	//从polys里面得到所有的points
		glBegin(GL_LINE_LOOP);	//开始绘制直线
		for (int j = 0; j < points.size(); j++)
		{
			glVertex3f(points[j].longitude, points[j].latitude, 0.0);	//x，y坐标
		}
		glEnd();
	}
	glFlush();
}
void init(void)
{
	//设置背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//初始化观察值
	glMatrixMode(GL_PROJECTION);    //将矩阵模式设为投影
	glLoadIdentity();                 //对矩阵进行单位化
	glOrtho(110.0, 118.0, 30.0, 38.0, -1.0, 1.0);   //构造平行投影矩阵
}
int main(int argc, char** argv)
{
	// 数据文件目录
	const char *filename = "E:/河南地图经纬度数据.txt";
	polys = ReadMapData(filename);	//从文件中读取的坐标存储到polys中
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//单缓存和RGB
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("地图绘制");
	init();
	glutDisplayFunc(display);     //显示回调函数
	glutMainLoop();
	return 0;
}

#include<windows.h>
#include<GL/glut.h>
const int POINTNUM = 5;      //多边形点数.

/******定义结构体用于活性边表AET和新边表NET***********************************/
typedef struct XET
{
	float x;
	float dx, ymax;
	XET* next;
} AET, NET;

/******定义点结构体point******************************************************/
struct point
{
	float x;
	float y;
} polypoint[POINTNUM] = { {400,200},{1300,200},{1500,500},{1000,1100},{200,700} }; //多边形顶点

void PolyScan()
{
	/******计算最高点的y坐标(扫描到此结束)****************************************/
	int MaxY = 0;
	int i;
	for (i = 0; i < POINTNUM; i++)
		if (polypoint[i].y > MaxY)
			MaxY = polypoint[i].y;


	/******初始化NET表************************************************************/
	NET *pNET[1200];
	for (i = 0; i <= MaxY; i++)
	{
		pNET[i] = new NET;
		pNET[i]->next = nullptr;
	}
	/******扫描并建立NET表*********************************************************/
	for (i = 0; i <= MaxY; i++)
	{
		for (int j = 0; j < POINTNUM; j++)
			if (polypoint[j].y == i)
			{
				//一个点跟前面的一个点形成一条线段，跟后面的点也形成线段
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

	/*******初始化AET表***********************************************************/
	AET *pAET = new AET;
	pAET->next = nullptr;
	/******建立并更新活性边表AET*****************************************************/
	for (i = 0; i <= MaxY; i++)
	{
		//计算新的交点x,更新AET
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}
		//更新后新AET先排序*************************************************************/
		//断表排序,不再开辟空间
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
		//(改进算法)先从AET表中删除ymax==i的结点****************************************/
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
		//将NET中的新点加入AET,并用插入法按X值递增排序**********************************/
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
		/******配对填充颜色***************************************************************/
		glClear(GL_COLOR_BUFFER_BIT);        //赋值的窗口显示.
		glColor3f(0.0, 0.0, 0.0);             //设置直线的颜色红色
		glBegin(GL_POINTS);
		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				glVertex2i(static_cast<int>(j), i);
			p = p->next->next;//考虑端点情况
		}
	}
	glEnd();
	glFlush();
}

void init(int argc, char** argv)
{
	glutInit(&argc, argv);  //I初始化 GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //设置显示模式：单个缓存和使用RGB模型
	glutInitWindowPosition(50, 100);  //设置窗口的顶部和左边位置
	glutInitWindowSize(800, 600);  //设置窗口的高度和宽度
	glutCreateWindow("Test");

	glClearColor(1.0, 1.0, 1.0, 0); //窗口背景颜色为白色
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
	glutDisplayFunc(myDisplay);        //图形的定义传递给我window.
	glutMainLoop();
	return 0;
}
