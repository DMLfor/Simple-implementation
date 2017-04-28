#ifndef SOLARSYSTEM_H_INCLUED
#define SOLARSYSTEM_H_INCLUED
#include <GL/glut.h>
#define STARS_NUM 10
class Star
{
public:
	GLfloat radius;
	// 半径
	GLfloat speed, selfSpeed;
	//公转速度和自转速度
	GLfloat distance;
	//到父节点的距离
	GLfloat rgbaColor[4];
	//星球的颜色
	Star* parentStar;
	//父节点星球
	Star(GLfloat __radius, GLfloat __distance, GLfloat __speed,
			GLfloat __selfSpeed, Star* __parent);
	//构造函数，构造一个星球需要有半径，到父节点的距离，公转速度
	//自转速度，父节点

	void drawStar();

	virtual void draw() { drawStar(); }

	virtual void update(long timeSpan);
protected:
	GLfloat alphaSelf, alpha;
	//当前自转角度，公转角度
};

class Planet : public Star
{
public:
	Planet(GLfloat __radius, GLfloat __distance, GLfloat __speed
		,GLfloat __selfSpeed, Star* __parent, GLfloat __rgbColor[]);

	void drawPlanet();
	virtual void draw(){ drawPlanet(); drawStar(); }

};

class LightPlanet : public Planet
{
public:
	LightPlanet(GLfloat __radius, GLfloat __distance, GLfloat __speed
			,GLfloat __selfSpeed, Star* __parent, GLfloat __rgbColor[]);
	void drawLight();
	virtual void draw() { drawLight(); drawPlanet(); drawStar(); }
};

class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void onDisplay();
	void onUpdate();
	void onKeyboard(unsigned char key, int x, int y);
private:
	Star* stars[STARS_NUM];
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};
#endif
