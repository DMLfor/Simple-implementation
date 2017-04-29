#ifndef SOLARSYSTEM_H_INCLUED
#define SOLARSYSTEM_H_INCLUED
#include <GL/glut.h>
#define STARS_NUM 10
class Star {
public:
    GLfloat radius;
    GLfloat speed, selfSpeed;
    GLfloat distance;
    GLfloat rgbaColor[4];

    Star* parentStar;

    Star(GLfloat radius, GLfloat distance,
         GLfloat speed,  GLfloat selfSpeed,
         Star* parent);
    void drawStar();
    virtual void draw() { drawStar(); }
    virtual void update(long timeSpan);
protected:
    GLfloat alphaSelf, alpha;
};

class Planet : public Star {
public:
    Planet(GLfloat radius, GLfloat distance,
           GLfloat speed,  GLfloat selfSpeed,
           Star* parent, GLfloat rgbColor[3]);
    void drawPlanet();
    virtual void draw() { drawPlanet(); drawStar(); }
};

class LightPlanet : public Planet {
public:
    LightPlanet(GLfloat Radius, GLfloat Distance,
                GLfloat Speed,  GLfloat SelfSpeed,
                Star* Parent, GLfloat rgbColor[]);
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
