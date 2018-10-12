#pragma once
#include "Vec3.h"
#include <GL/freeglut.h>
class Light
{
public:
	Light(Vec3, Vec3, Vec3, Vec3, float, int = 0, float = 0.f, float = 0.f, Vec3 = Vec3(0,0,1));
	~Light();
	void render();
	void setPos(Vec3);
	void setDir(Vec3);
	void setEnable(bool);
	bool isGood();

	void changeBrightness(float);
private:
	static bool lightFlags[8];

	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	Vec3 position;
	float type;
	int attenutaionType;
	float attenuationFactor;
	float cutoff;
	Vec3 direction;
	int lightHandle;
	bool good;
	bool enable;
};

