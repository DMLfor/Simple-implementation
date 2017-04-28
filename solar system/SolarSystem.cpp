#include "SolarSystem.h"
#include <cmath>
#include <cstdlib>
#define TIMEPAST 1
#define SELFROTATE 3
#define PI 3.1415926535
#define OFFSET 20
#define REST 700
#define REST_Y (-REST)
#define REST_Z (REST)
//运动速度
#define MER_SPEED   87.0
#define VEN_SPEED  225.0
#define EAR_SPEED  365.0
#define MOO_SPEED   30.0
#define MAR_SPEED  687.0
#define JUP_SPEED 1298.4
#define SAT_SPEED 3225.6
#define URA_SPEED 3066.4
#define NEP_SPEED 6014.8
//到太阳的距离
#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10
//公转半径
#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78
#define SET_VALUE_3(name, value0, value1, value2) \
	                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)
enum STARS{Sun, Mercury, Venus, Earth, Moon, Mars
	,Jupiter, Saturn, Uranus, Neptune};
void SolarSystem::onDisplay() 
{

	glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
	glClearColor(.7f, .7f, .7f, .1f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewX, viewY, viewZ, centerX, centerY, centerZ, upX, upY, upZ);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	for (int i=0; i<STARS_NUM; i++)
		stars[i]->draw();

	glutSwapBuffers();
	    // 实际绘制
		// for (int i=0; i<STARS_NUM; i++)
		// stars[i]->draw();
		//
		// glutSwapBuff
}

/*
void SolarSystem:: onDisplay()
{
	//　清除viewport 缓存区
	glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
	//　清空设置颜色缓存
	glClearColor(.7f, .7f, .7f, .1f);
	//　指定当前矩阵为投影矩阵
	glMatrixMode(GL_PROJECTION);
	//　将指定的矩阵指定为单位矩阵
	glLoadIdentity();
	//　指定当前的观察视景体
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	//　指定当前矩阵为视景矩阵堆栈应用术后的矩阵操作
	glMatrixMode(GL_MODELVIEW);
	//　指定当前的矩阵为单位矩阵
	glLoadIdentity();
	//　定义视图矩阵，并与当前矩阵相乘
	gluLookAt(viewX, viewY, viewZ, centerX, centerY, centerZ, upX, upY, upZ);
	//　设置第一个光源(0号光源)
	glEnable(GL_LIGHT0);
	//　启用光源
	glEnable(GL_LIGHTING);
	//　启用深度测试，根据坐标的远近自动隐藏被遮住的图形
	glEnable(GL_DEPTH_TEST);

	//　绘制星球
	for(int i = 0; i<STARS_NUM; i++)
		stars[i]->draw();

	// 我们在 main 函数中初始化显示模式时使用了 GLUT_DOUBLE
	// 需要使用 glutSwapBuffers 在绘制结束后实现双缓冲的缓冲区交换
	glutSwapBuffers();
}*/

void SolarSystem:: onUpdate()
{
	for(int i = 0; i<STARS_NUM; i++)
		stars[i]->update(TIMEPAST);

	onDisplay();
}

void SolarSystem:: onKeyboard(unsigned char key, int x, int y)
{
	switch (key){
		case 'w': viewY += OFFSET; break;
		case 's': viewZ += OFFSET; break;
		case 'S': viewZ -= OFFSET; break;
		case 'a': viewX -= OFFSET; break;
		case 'd': viewX += OFFSET; break;
		case 'x': viewY -= OFFSET; break;
		case 'r':
				  viewX = 0; viewY = REST_Y; viewZ = REST_Z;
				  centerX = centerY = centerZ = 0;
				  upX = upY = 0; upZ = 1;
				  break;
		case 27: exit(0); break;
		default: break;

	}
}
SolarSystem:: SolarSystem()
{
	viewX = 0;
	viewY = REST_Y;
	viewZ = REST_Z;
	centerX = centerY = centerZ = 0;
	upX = upY = 0;
	upZ = 1;

	GLfloat rgbColor[3] = {1, 0, 0};
	stars[Sun]     = new LightPlanet(SUN_RADIUS, 0, 0, SELFROTATE, 0, rgbColor);

	SET_VALUE_3(rgbColor, .2, .2, .5);
	stars[Mercury] = new Planet(MER_RADIUS, MER_DIS, MER_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, 1, .7, 0);
	stars[Venus]   = new Planet(VEN_RADIUS, VEN_DIS, VEN_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, 0, 1, 0);
	stars[Earth]   = new Planet(EAR_RADIUS, EAR_DIS, EAR_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, 1, 1, 0);
	stars[Moon]    = new Planet(MOO_RADIUS, MOO_DIS, MOO_SPEED, SELFROTATE, stars[Earth], rgbColor);

	SET_VALUE_3(rgbColor, 1, .5, .5);
	stars[Mars]    = new Planet(MAR_RADIUS, MAR_DIS, MAR_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, 1, 1, .5);
	stars[Jupiter] = new Planet(JUP_RADIUS, JUP_DIS, JUP_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, .5, 1, .5);

	SET_VALUE_3(rgbColor, .4, .4, .4);
	stars[Uranus]  = new Planet(URA_RADIUS, URA_DIS, URA_SPEED, SELFROTATE, stars[Sun], rgbColor);

	SET_VALUE_3(rgbColor, .5, .5, 1);
	stars[Neptune] = new Planet(NEP_RADIUS, NEP_DIS, NEP_SPEED, SELFROTATE, stars[Sun], rgbColor);

}

SolarSystem:: ~SolarSystem()
{
	for(int i = 0; i<STARS_NUM; i++)
		delete stars[i];
}

Star:: Star(GLfloat __radius, GLfloat __distance, GLfloat __speed
		,GLfloat __selfSpeed, Star* __parent)
{
	radius = __radius;
	distance = __distance;
	selfSpeed = __selfSpeed;
	parentStar = __parent;
	alphaSelf = alpha = 0;
	for(int i = 0; i<4; i++)
		rgbaColor[i] = 1.0f;

	if(speed > 0)
		speed = 360.0f / __speed;
	else speed = 0.0;

}

/*
void Star:: drawStar()
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;
	glPushMatrix();
	{
		//公转
		
		//如果是行星，且距离不为０，那么且向远点平移一个半径
		//这部分用于处理行星
		if(parentStar != 0 && parentStar->distance > 0)
		{
			
			//将绘制的图形沿z轴旋转alpha
			glRotatef(parentStar->alpha, 0, 0, 1);
			//x轴方向向上移distance, y, z方向不变
			glTranslatef(parentStar->distance, 0.0, 0.0);
		}
	//　绘制运行轨道
		glBegin(GL_LINES);
		for(int i = 0; i<n; i++)
			glVertex2f(distance * cos(2 * PI *i / n),
					distance * sin(2 * PI * i / n));
		glEnd();
		//　绕z轴旋转alpha
		glRotatef(alpha, 0, 0, 1);
		//　x轴方向平移 distance , y, z方向不变
		glTranslatef(distance, 0.0, 0.0);

		//自转
		glRotatef(alphaSelf, 0, 0, 1);

		//绘制行星颜色
		//
		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
		glutSolidSphere(radius, 40, 32);
	}
	//恢复绘制前的矩阵环境
	glPopMatrix();

}
*/
void Star::drawStar() {
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	int n = 1440;
	glPushMatrix();
	{
		if (parentStar != 0 && parentStar->distance > 0) {
			glRotatef(parentStar->alpha, 0, 0, 1);
			glTranslatef(parentStar->distance, 0.0, 0.0);

		}
		glBegin(GL_LINES);
		for(int i=0; i<n; ++i)
			glVertex2f(distance * cos(2 * PI * i / n),
					distance * sin(2 * PI * i / n));
		glEnd();
		glRotatef(alpha, 0, 0, 1);
		glTranslatef(distance, 0.0, 0.0);

		glRotatef(alphaSelf, 0, 0, 1);
		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
		glutSolidSphere(radius, 40, 32);

	}
	glPopMatrix();


}
void Star:: update(long timeSpan)
{
	alpha += timeSpan * speed; //更新角度
	alphaSelf += selfSpeed;     //更新自转角度
}

Planet:: Planet(GLfloat __radius, GLfloat __distance, GLfloat __speed
		,GLfloat __selfSpeed, Star* __parent, GLfloat __rgbColor[]):
	Star(__radius, __distance, __speed, __selfSpeed, __parent)
{
	for(int i = 0; i<3; i++)
		rgbaColor[i] = __rgbColor[i];
	rgbaColor[3] = 1.0f;	

}

void Planet:: drawPlanet()
{
	GLfloat mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat mat_emission[] = {rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]};
	GLfloat mat_shininess = 90.0f;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}


LightPlanet:: LightPlanet(GLfloat __radius, GLfloat __distance, GLfloat __speed
		,GLfloat __selfSpeed, Star* __parent, GLfloat __rgbColor[]):
	Planet(__radius, __distance, __speed, __selfSpeed, __parent, __rgbColor)
{
	;
}
void LightPlanet::drawLight() 
{

	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
