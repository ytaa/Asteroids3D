#include "DirectionMarker.h"



DirectionMarker::DirectionMarker(Object *_player, Object *_target)
	: player(_player)
	, target(_target)
	,rotationMatrix()
{
}


DirectionMarker::~DirectionMarker()
{
}

void DirectionMarker::update() {
	Vec3 z = target->getPos() - player->getPos();
	Vec3 x = Vec3(0,1,0).cross(z);
	Vec3 y = z.cross(x);

	x = x.normalized();
	y = y.normalized();
	z = z.normalized();

	rotationMatrix[0] = x.x;
	rotationMatrix[1] = x.y;
	rotationMatrix[2] = x.z;
	rotationMatrix[3] = 0;

	rotationMatrix[4] = y.x;
	rotationMatrix[5] = y.y;
	rotationMatrix[6] = y.z;
	rotationMatrix[7] = 0;

	rotationMatrix[8] = z.x;
	rotationMatrix[9] = z.y;
	rotationMatrix[10] = z.z;
	rotationMatrix[11] = 0;

	rotationMatrix[12] = 0;
	rotationMatrix[13] = 0;
	rotationMatrix[14] = 0;
	rotationMatrix[15] = 1;
}


void DirectionMarker::render() {
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);

	Vec3 dir = target->getPos() - player->getPos();
	dir = dir.normalized();
	Vec3 pos = player->getPos() + dir * 4.f;
	//std::cout << pos << std::endl;
	glTranslatef(pos.x, pos.y, pos.z);
	glMultMatrixf(rotationMatrix);
	glColor3f(35.f / 255.f, 17.f / 255.f, 20.f / 255.f);
	
	glutSolidCone(0.5f, 2.f, 20, 20);

	glDisable(GL_COLOR_MATERIAL);

	glPopMatrix();
}
