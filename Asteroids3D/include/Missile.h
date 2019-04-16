#pragma once
#include "Object.h"
#include "Vec3.h"

class Player;
class ParticleEmitter;

class Missile :
	public Object
{
public:
	Missile(Player *, Vec3, Vec3);
	~Missile();

	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	OType getType();

	unsigned int getLifetime();
	Player * getPlayer();

	bool isReadyToBeDeleted();
	bool isHit();

	void collide(ParticleEmitter *);

private:
	Player *player;
	Vec3 position;
	Vec3 velocity;
	float *rotationMatrix;

	unsigned int lifetime;
	bool readyToBeDeleted;
	bool hit;

	float radius;

	ParticleEmitter* particleEmitter;

	const OType type;

	static const unsigned int maxLifetime;
};

