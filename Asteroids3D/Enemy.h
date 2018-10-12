#pragma once
#include "Object.h"
#include "Meteor.h"
#include "DirectionMarker.h"
#include "Light.h"

class Enemy :
	public Object
{
public:
	Enemy(Object *, std::vector<Meteor *> *, Model3D * = NULL, Texture2D * = NULL);
	~Enemy();

	//From Object class
	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	OType getType();

	int getMaxHp();
	int getHp();
	Vec3 getVel();

	void setLight(Light *);
	void setParticleEmitter(ParticleEmitter *);

	void collide(Object *);

	void respawn();

private:
	void seek(Vec3);
	void flee(Vec3, float, float, float, float);

	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	Vec3 direction;
	
	float approachZone;
	float maxDesired;
	float maxVelocity;
	float minVelocity;
	float maxSteering;
	float predatorMaxSteering;
	float meteorMaxSteering;
	float maxAcceleration;

	float predatorFleeDistance;
	float predatorMaxFleeDistance;
	float meteorFleeDistance;
	float meteorMaxFleeDistance;

	float seekArea;

	int maxHealthPoints;
	int healthPoints;

	int minScore;
	int maxScore;
	int currentScore;
	int frameCounter;

	float radius;
	float rotationMatrix[16];

	Object *predator;
	std::vector<Meteor *> *meteors;

	DirectionMarker predatorDirectionMarker;

	Light* engineLight;
	ParticleEmitter* particleEmitter;

	Model3D *model;
	Texture2D *texture;
	float materialAmbient[4];
	float materialDiffuse[4];
	float materialSpecular[4];
	float shininess;

	OType type;

};

