#include <GL/glut.h>  
#include <stdlib.h>  
#include <stdio.h>  
#define stripeImageWidth 32   
  
GLubyte stripeImage[4 * stripeImageWidth];  //4*32的一维数组  
  
/* 
 * 255 0 0 255 
 * 255 0 0 255 
 * 255 0 0 255 
 * 255 0 0 255 
 * 0 255 0 255 
 *  ... 
 * 0 255 0 255 
 */  
void makeStripeImage(void) //生成纹理  
{  
    int j;  
    for (j = 0; j < stripeImageWidth; j++)  
    {  
        stripeImage[4 * j + 0] = (GLubyte)((j <= 4) ? 255 : 0);  
        stripeImage[4 * j + 1] = (GLubyte)((j > 4) ? 255 : 0);  
        stripeImage[4 * j + 2] = (GLubyte)0;  
        stripeImage[4 * j + 3] = (GLubyte)255;  
    }  
}  
  
// 平面纹理坐标生成  
static GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 1.0 };   //x=0  
static GLfloat slanted[] = { 1.0, 1.0, 1.0, 0.0 };  
static GLfloat *currentCoeff;  
static GLenum currentPlane;  
static GLint currentGenMode;  
static float roangles;  
  
//  纹理材质灯光初始化  
void init(void)  
{  
    glClearColor(1.0, 1.0, 1.0, 1.0);   //白色  
    glEnable(GL_DEPTH_TEST);        //开启更新深度缓冲区  
    glShadeModel(GL_SMOOTH);    //实现颜色过渡效果  
    makeStripeImage();  //纹理初始化  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  //设置像素存储模式，4字节对齐  
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //纹理环绕方式，1d纹理，设置成在s(x)方向上的被控行为，简单的重复纹理  
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //纹理过滤，放大使用线性过滤  
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //纹理过滤，缩小使用线性过滤  
    /* 
     * 生成与当前绑定的纹理对象在同一个目标上的纹理 
     * 手动设置每个多级渐远纹理的级别 
     * 纹理储存为RGB值 
     * 纹理宽度为32 
     * 原图的格式RGBA 
     * 数据类型unsigned byte 
     * 图像数据 
     */  
    glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,  
        GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);    //纹理贴图和材质混合  
    currentCoeff = xequalzero;  
    currentGenMode = GL_OBJECT_LINEAR;  
    currentPlane = GL_OBJECT_PLANE;  
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);   //纹理坐标自动生成，物体模式，纹理会跟随物体的转动而转动  
    glTexGenfv(GL_S, currentPlane, currentCoeff);  
    glEnable(GL_TEXTURE_GEN_S); //启用纹理处理  
    glEnable(GL_TEXTURE_1D);        //启用一维纹理  
    glEnable(GL_LIGHTING);  //启用光源  
    glEnable(GL_LIGHT0);        //启用0号光源  
    glEnable(GL_AUTO_NORMAL);   //光反射到各个方向  
    glEnable(GL_NORMALIZE);     //启用法向量  
    glFrontFace(GL_CW);     //顺时针多边形为正面  
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0);  //设置正面的镜面指数为64（值越大越近视镜面）  
    roangles = 45.0f;   //旋转角度  
}  
  
//  绘制图形  
void display(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    //保存移位矩阵对球体进行变换  
    glPushMatrix();  
    glRotatef(roangles, 0.0, 0.0, 1.0);     //旋转变换，绕z轴  
    glutSolidSphere(2.0, 32, 32);   //绘制球体，半径2，经纬均为32  
    glPopMatrix();  
    glFlush();  
}  
  
void reshape(int w, int h)  
{  
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);//左下角(0,0)，右上角(w,h)  
    glMatrixMode(GL_PROJECTION);//投影  
    glLoadIdentity();//重置单位矩阵  
    if (w <= h)  
        glOrtho(-3.5, 3.5, -3.5*(GLfloat)h / (GLfloat)w,  
            3.5*(GLfloat)h / (GLfloat)w, -3.5, 3.5);//w<=h,左下近(-3.5,-3.5*h/w,-3.5),右上远(3.5,3.5*h/w,3.5)  
    else  
        glOrtho(-3.5*(GLfloat)w / (GLfloat)h,  
            3.5*(GLfloat)w / (GLfloat)h, -3.5, 3.5, -3.5, 3.5);//w>h,左下近(-3.5*w/h,-3.5,-3.5)，右上远(3.5*w/h,3.5,3.5)  
    glMatrixMode(GL_MODELVIEW);//模型视图  
    glLoadIdentity();//重置单位矩阵  
}  
  
void idle()  
{  
    roangles += 0.05f;  //控制旋转速度  
    glutPostRedisplay();  
}  
  
int main(int argc, char** argv)  
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(256, 256);//窗口大小  
    glutInitWindowPosition(100, 100);//窗口坐标  
    glutCreateWindow(argv[0]);  
    glutIdleFunc(idle);  
    init();  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  
    glutMainLoop();  
    return 0;  
}