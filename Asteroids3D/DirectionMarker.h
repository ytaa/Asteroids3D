#pragma once
#include "Object.h"
class DirectionMarker
{
public:
	DirectionMarker(Object *, Object *);
	~DirectionMarker();

	void update();
	void render();

private:
	Object* player;
	Object* target;
	float rotationMatrix[16];

};

