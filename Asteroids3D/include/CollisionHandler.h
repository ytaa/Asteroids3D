#pragma once
#include <vector>
#include "Vec3.h"
#include "Object.h"
#include "Player.h"
#include "Meteor.h"
#include "Missile.h"
#include "PlayerTarget.h"
#include "ParticleEmitter.h"
#include "Enemy.h"

class Scene;

class CollisionHandler
{
public:
	CollisionHandler(Scene *, std::vector<Object *> *);
	~CollisionHandler();
	void update();
private:
	void collide(Object*, Object*);
	void applyElasticCollision(Meteor*, Meteor*);

	Scene *scene;
	std::vector<Object*> *objects;
};

