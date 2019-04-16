#include "Missile.h"
#include "Player.h"
#include "ParticleEmitter.h"

const unsigned int Missile::maxLifetime = 90; //frames

Missile::Missile(Player *_player, Vec3 _position, Vec3 _velocity)
	:player(_player)
	,position(_position)
	,velocity(_velocity)
	,rotationMatrix(new float[16])
	,lifetime(maxLifetime)
	,readyToBeDeleted(false)
	,hit(false)
	,radius(0.15f)
	,particleEmitter(NULL)
	,type(OType::OMissile)
{
	Vec3 z = player->getDir();
	Vec3 y = player->getUp();
	Vec3 x = z.cross(y);

	x = x.normalized();

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


Missile::~Missile()
{
	delete[] rotationMatrix;
	if (particleEmitter) {
		delete particleEmitter;
	}
}

int Missile::update() {
	position+=velocity;
	if (lifetime > 0)
		lifetime--;
	if (hit == true) {
		if (particleEmitter->isDead() == true) {
			delete particleEmitter;
			particleEmitter = NULL;
			readyToBeDeleted = true;
			return -1;
		}
	}
	else if (lifetime == 0) {
		readyToBeDeleted = true;
		return -1;
	}
	return 0;
}
void Missile::render() {
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);
	//glDisable(GL_CULL_FACE);

	glTranslatef(position.x, position.y, position.z);
	glMultMatrixf(rotationMatrix);
	glScalef(1.f, 1.f, 15.f);
	
	//glColor3f(150.f / 255.f, 17.f / 255.f, 20.f / 255.f);
	glColor4f(150.f / 255.f, 17.f / 255.f, 20.f / 255.f, 0.7f);

	glutSolidSphere(radius, 5, 5);

	glDisable(GL_COLOR_MATERIAL);
	//glEnable(GL_CULL_FACE);

	glPopMatrix();
}
Vec3 Missile::getPos() {
	return position;
}
Vec3 Missile::getDir() {
	return Vec3(rotationMatrix[8], rotationMatrix[9], rotationMatrix[10]);
}
Vec3 Missile::getUp() {
	return Vec3(rotationMatrix[4], rotationMatrix[5], rotationMatrix[6]);
}
float Missile::getRadius() {
	return radius;
}
OType Missile::getType() {
	return type;
}

unsigned int Missile::getLifetime() {
	return lifetime;
}
Player* Missile::getPlayer() {
	return player;
}

bool Missile::isReadyToBeDeleted() {
	return readyToBeDeleted;
}
bool Missile::isHit() {
	return hit;
}

void Missile::collide(ParticleEmitter *pe) {
	hit = true;
	particleEmitter = pe;
}