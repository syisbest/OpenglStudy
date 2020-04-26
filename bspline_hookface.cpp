#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
GLfloat ctrlpoints[4][4][3] = {
	{   {-3,0,4.0},
		{-2,0,2.0},
		{-1,0,0.0},
		{0,0,2.0}},
	{	{-3,1,1.0},
		{-2,1,3.0},
		{-1,1,6.0},
		{0,1,-1.0}},
	{	{-3,2,4.0},
		{-2,2,0.0},
		{-1,2,3.0},
		{0,2,4.0}},
	{	{-3,3,0.0},
		{-2,3,0.0},
		{-1,3,0.0},
		{0,3,0.0}}
};
GLUnurbsObj *theNurb;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	GLfloat ambient[] = { 0.2, 0.1, 0.5, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.2, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 0.2, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 45.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);//创建光源 RGBA模式下环境光
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//光源位置齐次坐标 (x, y, z, w)设置。
	//第四个参数w为0.0时，定义相应的光源是定向光源，其所有的光线几乎是互相平行的
	//w为1.0时，光源为定位光源
	//光源方向由定义的坐标(x, y, z)
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);//定义材质  材料的漫反射光颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//镜面指数光亮度
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 5.0);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1, 0.1, 0.1);
	GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0,1.0, 1.0, 1.0, 1.0 };////B样条控制向量
	glRotatef(1.0, 0.8, 0.7, 0.5); // 旋转变换  
	gluBeginSurface(theNurb); // 开始曲面绘制 							 
	gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctrlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3); // 定义曲面的数学模型，确定其形状  
	gluEndSurface(theNurb); // 结束曲面绘制  
	glutSwapBuffers();
	/*void gluNurbsSurface(
		GLUnurbs            *nobj,
		GLint               sknot_count, //节点数量
		float               *sknot, //节点序列
		GLint               tknot_count, //节点数量
		GLfloat             *tknot, //节点序列
		GLint               s_stride, //每个参数化方向上控制点之间的浮点值的数量
		GLint               t_stride,
		GLfloat             *ctlarray, //指向包含了控制点的数组
		GLint               sorder, //表面多项式的阶数
		GLint               torder, //表面多项式的阶数
		GLenum              type);//表示二维求值器类型
*/
}
void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0*(GLfloat)h / (GLfloat)w, 5.0*(GLfloat)h / (GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-5.0*(GLfloat)w / (GLfloat)h, 5.0*(GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	srand((unsigned int)time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//使用双缓存模式和深度缓存
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("B样条曲面");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
