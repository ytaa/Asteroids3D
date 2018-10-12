#include "Meteor.h"

const float Meteor::minVelocity = 0.3f;
const float Meteor::maxVelocity = 0.8f;
const float Meteor::minRadius = 5.f;
const float Meteor::maxRadius = 40.f;


Meteor::Meteor(Vec3 _pos, Vec3 _velocity, float _r, Model3D *_model, std::vector<Texture2D> *_textures)
	:position(_pos)
	,velocity(_velocity)
	,radius(_r)
	,rotateX(rng::rand(0.f,180.f))
	,rotateY(rng::rand(0.f, 180.f))
	,rotateZ(rng::rand(0.f, 180.f))
	,maxHealthFactor(1.25f)
	,healthPoints((int)(radius*maxHealthFactor))
	,dead(false)
	,currentTexture(0)
	,particleEmitter(NULL)
	,randAmbientOffset(rng::rand(-0.025f, 0.025f))
	,model(_model)
	,textures(_textures)
	,type(OType::OMeteor)
{
}


Meteor::~Meteor()
{
	if (particleEmitter)
		delete particleEmitter;
}

int Meteor::update()
{
	if (particleEmitter) {
		if (particleEmitter->isDead() == true) {
			delete particleEmitter;
			particleEmitter = NULL;
			dead = true;
		}
	}
	else {
		position = position + velocity;
	}
	return 0;
}

void Meteor::render() {
	if (healthPoints <= 0) {
		return;
	}

	glPushMatrix();
	//glColor3f(1.f, 1.f, 1.f);
	glTranslatef(position.x, position.y, position.z);  
	
	float mAmb[4] = { 0.135f+randAmbientOffset, 0.135f + randAmbientOffset, 0.135f + randAmbientOffset, 1.0f };
	//float mDif[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	//float mSpe[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float mDif[4] = { 0.5f + randAmbientOffset, 0.5f + randAmbientOffset, 0.5f + randAmbientOffset, 1.0f };
	float mSpe[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpe);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.f);
	
	if (model) {
		glRotatef(rotateX, 1.f, 0.f, 0.f);
		glRotatef(rotateY, 0.f, 1.f, 0.f);
		glRotatef(rotateZ, 0.f, 0.f, 1.f);
		glScalef(radius/100.f, radius/100.f, radius/100.f);
		if (textures) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures->at(currentTexture).getId());
			model->call();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			model->call();
		}
	}
	else
		glutSolidSphere(radius, 20, 20);
	//glutSolidCube(radius);
	glPopMatrix();
}

Vec3 Meteor::getPos() {
	return position;
}
Vec3 Meteor::getDir() {
	return velocity.normalized();
}
Vec3 Meteor::getUp() {
	return Vec3(0,1,0);
}
Vec3 Meteor::getVel() {
	return velocity;
}
float Meteor::getRadius() {
	return radius;
}
OType Meteor::getType() {
	return type;
}
void Meteor::setPos(Vec3 _position) {
	position = _position;
}
void Meteor::setVel(Vec3 _velocity) {
	velocity = _velocity;
}
void Meteor::setParticleEmitter(ParticleEmitter *_pe) {
	if(healthPoints <= 0 && particleEmitter == NULL)
		particleEmitter = _pe;
}
int Meteor::getHp() {
	return healthPoints;
}
bool Meteor::isDead() {
	return dead;
}
void Meteor::respawn(Vec3 targetPos, float arenaSize) {
	int randomWall = rng::rand(0,6);
	arenaSize /= 2;
	if (randomWall < 1) {
		position = Vec3(targetPos.x + arenaSize + maxRadius, rng::rand(targetPos.y-arenaSize, targetPos.y + arenaSize), rng::rand(targetPos.z - arenaSize, targetPos.z + arenaSize));
		velocity = Vec3(rng::rand(-maxVelocity, -minVelocity), rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity));
	}
	else if (randomWall < 2) {
		position = Vec3(targetPos.x - arenaSize - maxRadius, rng::rand(targetPos.y - arenaSize, targetPos.y + arenaSize), rng::rand(targetPos.z - arenaSize, targetPos.z + arenaSize));
		velocity = Vec3(rng::rand(minVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity));
	}
	else if (randomWall < 3) {
		position = Vec3(rng::rand(targetPos.x - arenaSize, targetPos.x + arenaSize), targetPos.y + arenaSize + maxRadius, rng::rand(targetPos.z - arenaSize, targetPos.z + arenaSize));
		velocity = Vec3(rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, -minVelocity), rng::rand(-maxVelocity, maxVelocity));
	}
	else if (randomWall < 4) {
		position = Vec3(rng::rand(targetPos.x - arenaSize, targetPos.x + arenaSize), targetPos.y - arenaSize - maxRadius, rng::rand(targetPos.z - arenaSize, targetPos.z + arenaSize));
		velocity = Vec3(rng::rand(-maxVelocity, maxVelocity), rng::rand(minVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity));
	}
	else if (randomWall < 5) {
		position = Vec3(rng::rand(targetPos.x - arenaSize, targetPos.x + arenaSize), rng::rand(targetPos.y - arenaSize, targetPos.y + arenaSize), targetPos.z + arenaSize + maxRadius);
		velocity = Vec3(rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, -minVelocity));
	}
	else {
		position = Vec3(rng::rand(targetPos.x - arenaSize, targetPos.x + arenaSize), rng::rand(targetPos.y - arenaSize, targetPos.y + arenaSize), targetPos.z - arenaSize - maxRadius);
		velocity = Vec3(rng::rand(-maxVelocity, maxVelocity), rng::rand(-maxVelocity, maxVelocity), rng::rand(minVelocity, maxVelocity));
	}
	healthPoints = (int)(radius*maxHealthFactor);
	dead = false;
	currentTexture = 0;
	//velocity = targetPos - position;
	//velocity = velocity + Vec3::random(0, minVelocity);
	//velocity = velocity.normalized()*rng::randFloat(minVelocity, maxVelocity);
}

void Meteor::collide(Object *ob) {
	if (ob->getType() == OType::OMissile) {
		healthPoints -= 1;
		if (healthPoints > 0) {
			currentTexture = (int)(textures->size() - ceil((((float)healthPoints / ((int)(radius*maxHealthFactor)))*textures->size())));
		}

	}
}