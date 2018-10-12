#pragma once
#include "Object.h"
class CameraTarget :
	public Object
{
public:
	CameraTarget();
	~CameraTarget();

	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	OType getType();

	Vec3 position;
	Vec3 direction;
	Vec3 up;
private:
	const OType type;
};

