#pragma once
#include <iostream>
#include <cmath>
#include "Object.h"
#include "Vec3.h"
#include "Model3D.h"
#include "Texture2D.h"
#include "Light.h"
#include "ParticleEmitter.h"
#include "State.h"



class PlayerTarget;
class Scene;
class Missile;


class Player :
	public Object
{
public:
	Player(Scene *, GMode, Model3D * = NULL, Texture2D * = NULL, Light * = NULL, Light * = NULL, Vec3 = Vec3(0, 0, 0));
	~Player();

	//inherited from Object
	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();

	int getMaxHP();
	int getHP();
	float getThrust();
	unsigned int getScore();
	OType getType();
	std::vector<Vec3> getBoundaryPoints();
	int getTimeLeft();
	GMode getGameMode();

	void changePitch(bool);
	void changeYaw(bool);
	void changeRoll(bool);
	void changeThrust();
	void changeDrag();

	void setLights(Light *, Light *);
	void setScore(unsigned int);
	void setMaxHp(int);
	void setTimeLeft(int);

	bool isInviolable();

	void fireMissile();
	void collide(Object *);

private:
	Vec3 position;
	Vec3 direction;
	Vec3 up;
	Vec3 left;

	float radius;
	float scale;

	GLfloat *matrixMultiplcation(GLfloat*, GLfloat*);
	void applyPitch();
	void applyYaw();
	void applyRoll();

	Vec3 rotationVelocity;
	Vec3 rotationAcceleration;
	Vec3 rotationDeacceleration;
	Vec3 rotationMaxVelocity;
	Vec3 rotationEnableFlag;

	float thrustVelocity;
	float thrustAcceleration;
	float thrustDeacceleration;
	float thrustMaxVelocity;
	float thrustEnableFlag;

	float dragVelocity;
	float dragAcceleration;
	float dragDeacceleration;
	float dragMaxVelocity;
	float dragEnableFlag;

	GLfloat *rotationMatrix;
	GLfloat *pitchMatrix;
	GLfloat *rollMatrix;
	GLfloat *yawMatrix;

	Light* engineLightNear;
	Light* engineLightFar;

	Model3D *model;
	Texture2D *texture;
	float materialAmbient[4];
	float materialDiffuse[4];
	float materialSpecular[4];
	float shininess;

	int maxHealthPoints;
	int healthPoints;
	unsigned int score;
	unsigned int maxInviolabilityTicks;
	unsigned int inviolabilityTicks;
	std::vector<Missile *> missiles;

	float missileFireVelocity;
	unsigned int missileFireRate;
	unsigned int missileFireTicks;

	GMode gameMode;
	int timeLeft;

	Scene *scene;
	
	const OType type;
};

