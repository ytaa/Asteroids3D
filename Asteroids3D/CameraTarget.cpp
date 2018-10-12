#include "CameraTarget.h"



CameraTarget::CameraTarget()
	:position(Vec3(2,2,1))
	,direction(Vec3(0,0,-1))
	,up(Vec3(0,1,0))
	,type(OType::OCameraTarget)
{
}


CameraTarget::~CameraTarget()
{
}

int CameraTarget::update() {
	return 0;
}

void CameraTarget::render() {}

Vec3 CameraTarget::getPos() {
	return position;
}

Vec3 CameraTarget::getDir() {
	return direction;
}

Vec3 CameraTarget::getUp() {
	return up;
}

float CameraTarget::getRadius() {
	return 0.f;
}
OType CameraTarget::getType() {
	return type;
}

