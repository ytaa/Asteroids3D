#pragma once
#include "Object.h"
#include "DirectionMarker.h"


class Player;
class Model3D;

class PlayerTarget :
	public Object
{
public:
	PlayerTarget(Player *, Model3D * = NULL);
	~PlayerTarget();
	
	//inherited from Object
	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	unsigned int getScore();
	OType getType();

	void respawn();

private:
	float spawningAreaMax;
	float spawningAreaMin;
	Player *player;
	DirectionMarker playerDirectionMarker;

	Vec3 position;
	Vec3 direction;

	float radius;
	unsigned int score;
	unsigned int minScore;
	unsigned int maxScore;
	unsigned int frameCounter;

	Model3D *model;

	const OType type;
};

