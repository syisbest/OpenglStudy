#include <gl/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
#define PI 3.1415926
void Rotate();
//水星、金星、地球、火星、木星、土星、天王星、海王星 
//adam,hesper,earth,mars,jupiter,saturn,uranus,neptune 
static float year = 0, day = 0, adamYear = 0, hesperYear = 0, marsYear = 0, jupiterYear = 0, saturnYear = 0, uranusYear = 0, neptuneYear = 0, sunYear = 0, month = 0;
static float mar_satellite_1, mar_satellite_2;
float light_angle = 0;
float light_radius = 8.0;
double x = 0, y = 0;
double aix_x = 0.0, aix_y = 0.5, aix_z = 0.5;
GLdouble angle = 100.0;
void lPosition()
{
	float y, z;
	y = light_radius * cos(light_angle);
	z = light_radius * sin(light_angle);
	float light_position[] = { 3.0,y,z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
void init(void)
{
	glClearColor(0.0, 0.1, 0.1, 0.1);//背景
	lPosition();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glEnable(GL_COLOR_MATERIAL);
}
void material_sun()                               //设置太阳材质，以下同
{
	GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.0,0.0,0.0,1.0 };        //太阳颜色为红色      
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_adam()
{
	GLfloat specular[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.3,1.0,0.2,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_hesper()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_earth()
{
	GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.1,0.2,0.6,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_mars()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.0,0.1,0.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_jupiter()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.8,0.7,0.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_saturn()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.6,0.6,0.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_uranus()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.3,0.3,0.7,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_neptune()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.0,0.1,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_moon()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.0,1.0,0.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_mar_satellite_1()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.0,1.0,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_mar_satellite_2()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_neptune_satellite_1()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 1.0,0.0,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_neptune_satellite_2()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_uranus_satellite_1()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.3,0.2,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_uranus_satellite_2()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.3,0.4,0.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_jupiter_satellite()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.3,0.6,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void material_saturn_satellite()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lmodel_ambient[] = { 0.3,0.6,1.0,1.0 };
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void sun()                  //绘制太阳
{
	glPushMatrix();
	material_sun();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);   //太阳自转
	glutSolidSphere(10, 200, 200);                //画球体        
	glPopMatrix();
}
void adam()               //水星
{
	glPushMatrix();
	material_adam();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)adamYear, aix_x, aix_y, aix_z);    //水星公转周期
	glTranslatef(15, 0, 0);
	glTranslatef(0.2, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);        //水星自转
	glTranslatef(-0.5, 0, 0);
	glTranslatef(0.5, 0, 0);
	glutSolidSphere(0.5, 20, 16);
	glPopMatrix();
}
void hesper()
{
	glPushMatrix();
	material_hesper();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)hesperYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(0.8, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-1, 0, 0);
	glTranslatef(1, 0, 0);
	glutSolidSphere(0.8, 20, 16);
	glPopMatrix();
}
void earth()
{
	glPushMatrix();
	material_earth();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)year, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(2, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-2, 0, 0);
	glTranslatef(2, 0, 0);
	glutSolidSphere(1.0, 20, 16);
	material_moon();                          //绘制月球，以下以同样方法绘制各行星的卫星
	glRotatef(month / 100, 0.0, 0.0, 1.0);
	glTranslatef(2, 0.0, 0.0);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();
}
void mars()
{
	glPushMatrix();
	material_mars();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)marsYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(7, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-7, 0, 0);
	glTranslatef(7, 0, 0);
	glutSolidSphere(0.6, 20, 16);
	glPushMatrix();
	material_mar_satellite_1();
	glRotatef(month / 20, 0.0, 1.0, 0.0);
	glTranslatef(1, 0.0, 0.0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
	glPushMatrix();
	material_mar_satellite_2();
	glRotatef(month / 46, 0.0, 1.0, 0.0);
	glTranslatef(1.5, 0.0, 0.0);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
	glPopMatrix();
}
void jupiter()
{
	glPushMatrix();
	material_jupiter();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)jupiterYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(13, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-13, 0, 0);
	glTranslatef(13, 0, 0);
	glutSolidSphere(2.0, 20, 16);
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.25, 5.0, 5, 64);
	glRotatef(-90, 1.0, 0, 0.0);

	material_jupiter_satellite();
	glRotatef(90, 1.0, 0, 0.0);
	glRotatef(month / 58, 0.0, 1.0, 0.0);
	glTranslatef(3, 0.0, 0.0);
	glutSolidSphere(0.6, 10, 10);

	glPopMatrix();
	glPopMatrix();
}
void saturn()
{
	glPushMatrix();
	material_saturn();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)saturnYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(20, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-20, 0, 0);
	glTranslatef(20, 0, 0);
	glRotatef(0.3, 1.0, 0.0, 0.0);
	glutSolidSphere(1.4, 20, 16);
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.1, 3.0, 5, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	material_saturn_satellite();
	glRotatef(month / 76, 0.0, 1.0, 0.0);
	glTranslatef(2.7, 0.0, 0.0);
	glutSolidSphere(0.4, 10, 10);
	glPopMatrix();
	glPopMatrix();
}
void uranus()
{
	glPushMatrix();
	material_uranus();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)uranusYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(28, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-28, 0, 0);
	glTranslatef(28, 0, 0);
	glRotatef(0.5, 1.0, 0.0, 0.0);
	glutSolidSphere(1.5, 20, 16);
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.1, 3.0, 5, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glPushMatrix();
	material_uranus_satellite_1();
	glRotatef(month / 108, 0.0, 1.0, 0.0);
	glTranslatef(2, 0.0, 0.0);
	glutSolidSphere(0.23, 10, 10);
	glPopMatrix();
	glPushMatrix();
	material_uranus_satellite_2();
	glRotatef(month / 145, 0.0, 1.0, 0.0);
	glTranslatef(3.5, 0.0, 0.0);
	glutSolidSphere(0.35, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void neptune()
{
	glPushMatrix();
	material_neptune();
	glTranslatef(-15, 0, 0);
	glRotatef((GLfloat)neptuneYear, aix_x, aix_y, aix_z);
	glTranslatef(15, 0, 0);
	glTranslatef(32, 0, 0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glTranslatef(-32, 0, 0);
	glTranslatef(32, 0, 0);
	glRotatef(0.5, 1.0, 0.0, 0.0);
	glutSolidSphere(1.3, 20, 16);
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0.0);
	glutSolidTorus(0.1, 3.0, 5, 64);
	glRotatef(-90, 1.0, 0, 0.0);
	glPushMatrix();
	material_neptune_satellite_1();
	glRotatef(month / 347, 0.0, 1.0, 0.0);
	glTranslatef(2.5, 0.0, 0.0);
	glutSolidSphere(0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	material_neptune_satellite_2();
	glRotatef(month / 389, 0.0, 1.0, 0.0);
	glTranslatef(3.5, 0.0, 0.0);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void display(void)
{
	lPosition();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sun();
	adam();
	hesper();
	earth();
	mars();
	jupiter();
	saturn();
	uranus();
	neptune();
	Rotate();
	glutSwapBuffers();
}
void myidle()
{
	day += 10.0;
	if (day >= 360)
		day = day - 360;
	glutPostRedisplay();
}
void Rotate()          //设置各行星的公转周期
{
	adamYear += 0.12;
	if (adamYear >= 360)
		adamYear -= 360;
	hesperYear += 0.10;
	if (hesperYear >= 360)
		hesperYear -= 360;
	year += 0.08;
	if (year >= 360)
		year -= 360;
	marsYear += 0.06;
	if (marsYear >= 360)
		marsYear -= 360;
	jupiterYear += 0.05;
	if (jupiterYear >= 360)
		jupiterYear -= 360;
	saturnYear += 0.04;
	if (saturnYear >= 360)
		saturnYear -= 360;
	uranusYear += 0.03;
	if (uranusYear >= 360)
		uranusYear -= 360;
	neptuneYear += 0.01;
	if (neptuneYear >= 360)
		neptuneYear -= 360;
	glutPostRedisplay();
	month += 0.03;
	if (month >= 360)
		month -= 360;
}
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'U':
	case 'u':
		aix_y -= 0.01;
		aix_z += 0.01;
		break;
	case 'D':
	case 'd':
		aix_y += 0.01;
		aix_z -= 0.01;
		break;
	case 'W':
	case 'w':
		angle -= 10.0;
		break;
	case 'S':
	case 's':
		angle += 10.0;
		break;
	}
	glutPostRedisplay();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -50.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("太阳系九大行星");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(myidle);
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}



