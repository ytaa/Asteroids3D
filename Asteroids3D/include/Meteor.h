#pragma once
#include <GL/freeglut.h>
#include "Object.h"
#include "Vec3.h"
#include "Model3D.h"
#include "Texture2D.h"
#include "rng.h"
#include "ParticleEmitter.h"
class Meteor :
	public Object
{
public:
	Meteor(Vec3, Vec3, float = 1.f, Model3D * = NULL, std::vector<Texture2D> * = NULL);
	~Meteor();
	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	Vec3 getVel();
	float getRadius();
	OType getType();

	void setPos(Vec3);
	void setVel(Vec3);
	void setParticleEmitter(ParticleEmitter *);

	int getHp();

	bool isDead();
	
	void respawn(Vec3, float);
	void collide(Object *);

	static const float minVelocity;
	static const float maxVelocity;

	static const float minRadius;
	static const float maxRadius;
private:
	Vec3 position;
	Vec3 velocity;
	
	float radius;
	float rotateX;
	float rotateY;
	float rotateZ;

	float maxHealthFactor;
	int healthPoints;
	bool dead;
	int currentTexture;
	ParticleEmitter* particleEmitter;
	
	float randAmbientOffset;

	Model3D *model;
	std::vector<Texture2D> *textures;

	const OType type;
};

