#pragma once
#include "Vec3.h"
#include <GL/freeglut.h>
enum OType {
	OPlayer,
	OMeteor,
	OCameraTarget,
	OSkyBox,
	OPlayerTarget,
	OMissile,
	OParticleEmitter,
	OEnemy
};

class Object {
public:
	Object();
	virtual ~Object();

	virtual int update() = 0;
	virtual void render() = 0;
	virtual Vec3 getPos() = 0;
	virtual Vec3 getDir() = 0;
	virtual Vec3 getUp() = 0;
	virtual float getRadius() = 0;
	virtual OType getType() = 0;
private:
};