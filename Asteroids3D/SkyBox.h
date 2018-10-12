#pragma once
#include "Object.h"
#include "Model3D.h"
#include "Texture2D.h"
class SkyBox :
	public Object
{
public:
	SkyBox(Object &, Model3D *, Texture2D *, float);
	~SkyBox();
	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	OType getType();
private:
	const OType type;
	Object& target;
	float scale;
	Model3D *model;
	Texture2D *texture;
};

