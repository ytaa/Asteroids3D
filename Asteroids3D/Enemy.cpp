#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(Object *_predator, std::vector<Meteor *> *_meteors, Model3D *_model, Texture2D *_texture)
	: position(Vec3::random(-200, 200))
	, velocity(Vec3(0.01f, 0.00000f, 0))
	, acceleration(Vec3())
	, direction(Vec3(0,0,1))
	, approachZone(25.f)
	, maxDesired(5.f)
	, maxVelocity(1.25f)
	, minVelocity(0.8f)
	, maxSteering(0.01f)
	, predatorMaxSteering(0.005f)
	, meteorMaxSteering(0.015f)
	, maxAcceleration(0.005f)
	, predatorFleeDistance(150.f)
	, predatorMaxFleeDistance(100.f)
	, meteorFleeDistance(50.f)
	, meteorMaxFleeDistance(30.f)
	, seekArea(200.f)
	, maxHealthPoints(15)
	, healthPoints(maxHealthPoints)
	, minScore(10)
	, maxScore(70)
	, currentScore(maxScore)
	, frameCounter(1)
	, radius(4.f)
	, rotationMatrix()
	, predator(_predator)
	, meteors(_meteors)
	, predatorDirectionMarker(DirectionMarker(predator, this))
	, model(_model)
	, texture(_texture)
	//, materialAmbient{ 0.2f, 0.12f, 0.01f, 1.0f }
	//, materialDiffuse{ 0.25f, 0.17f, 0.04f, 1.0f }
	, materialAmbient{ 0.12f, 0.12f, 0.18f, 1.0f }
	, materialDiffuse{ 0.17f, 0.17f, 0.22f, 1.0f }
	, materialSpecular{ 0.45f, 0.45f, 0.45f, 1.0f }
	, shininess(7.f)
	, type(OType::OEnemy)
{
}


Enemy::~Enemy()
{
	if (particleEmitter) {
		delete particleEmitter;
	}
}

int Enemy::update() {
	if (healthPoints <= 0) {
		if (predator->getType() == OType::OPlayer) {
			((Player *)predator)->setScore(((Player *)predator)->getScore() + currentScore);
		}
		respawn();
	}

	acceleration = 0;
	if (position.distance(Vec3(0, 0, 0)) > seekArea) {
		seek(Vec3(0, 0, 0) + (position - Vec3(0, 0, 0))*seekArea);
	}

	bool ignorePredator = false;
	

	//flee from player and meteors

	for (auto meteor : *meteors){
		if (meteor->getPos().distance(position) - meteor->getRadius() - radius < meteorFleeDistance) {
			if (meteor->getPos().distance(position) - meteor->getRadius() - radius < meteorMaxFleeDistance/2) {
				ignorePredator = true;
			}
			flee(meteor->getPos(), meteorFleeDistance, meteorMaxFleeDistance, meteorMaxSteering, meteor->getRadius());
		}
	}
	
/*	predatorPosQueue.push(predator->getPos());
	if (ignorePredator == false) {
		if (predator->getPos().distance(position) - predator->getRadius() - radius < predatorFleeDistance) {
			flee(predatorPosQueue.front(), predatorFleeDistance, predatorMaxFleeDistance, predatorMaxSteering, predator->getRadius());
			
		}
	}
	if (predatorPosQueue.size() > 30) {
		predatorPosQueue.pop();
	}*/

	if (ignorePredator == false) {
		if (predator->getPos().distance(position) - predator->getRadius() - radius < predatorFleeDistance) {
			flee(predator->getPos(), predatorFleeDistance, predatorMaxFleeDistance, predatorMaxSteering, predator->getRadius());

		}
	}

	if (acceleration.length() > maxAcceleration) {
		//acceleration = acceleration.normalized() * maxAcceleration;
	}

	//velocity += acceleration;

	position += velocity;

	if (velocity.length() > maxDesired) {
		//velocity = velocity.normalized() * maxVelocity;
	}

	if (!(velocity == Vec3(0.f, 0.f, 0.f))) {
		direction = velocity.normalized();
	}

	if (velocity.length() < minVelocity) {
		velocity = velocity.normalized() * minVelocity;
	}
	else if (velocity.length() > maxVelocity) {
		velocity = velocity.normalized() * maxVelocity;
	}

	//update light
	if (engineLight) {
		Vec3 lightFarPosVec = position - ((direction) * (radius*3.f));
		engineLight->setPos(lightFarPosVec);
	}
	//handle particle emitter
	if (particleEmitter) {
		if (particleEmitter->isDead() == true) {
			delete particleEmitter;
			particleEmitter = NULL;
		}
	}
	//update score
	frameCounter++;
	if (frameCounter % 61 == 0) {
		frameCounter = 1;
		if (currentScore > minScore) {
			currentScore -= 1;
		}
	}

	predatorDirectionMarker.update();

	//update rotationMatrix using new velocity
	Vec3 z = direction;
	Vec3 x = getUp().cross(z);
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

	return 0;
}
void Enemy::render() {
	glPushMatrix();

	

	glTranslatef(position.x, position.y, position.z);
	//glTranslatef(radius, radius, 0);
	glMultMatrixf(rotationMatrix);

	if (model) {
		glScalef(radius/100, radius/100, radius/250);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		if (texture) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture->getId());
			model->call();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			model->call();
		}

		glScalef(100/radius, 100/radius, 250/radius);
		glTranslatef(-radius*0.06f, -radius*0.12f, -radius*1.25f);
		glScalef(radius / 3.5f, radius / 3.5f, radius / 3.5f);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHTING);
		glColor3f(0.25f, 0.25f, 0.7f);
		glutSolidCone(1.f, 2.5f, 20, 20);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
	}
	else {
		glScalef(radius, radius, radius);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.15f, 0.25f, 0.15f);
		glutSolidCone(1.f, 2.5f, 20, 20);
		glDisable(GL_COLOR_MATERIAL);
	
	}

	glPopMatrix();

	//engine


	predatorDirectionMarker.render();
}
Vec3 Enemy::getPos() {
	return position;
}
Vec3 Enemy::getDir() {
	return direction;
}
Vec3 Enemy::getUp() {
	return Vec3(0,1,0);
}
float Enemy::getRadius() {
	return radius;
}
OType Enemy::getType() {
	return type;
}

int Enemy::getMaxHp() {
	return maxHealthPoints;
}
int Enemy::getHp() {
	return healthPoints;
}
Vec3 Enemy::getVel() {
	return velocity;
}

void Enemy::setLight(Light *_light) {
	engineLight = _light;
}
void Enemy::setParticleEmitter(ParticleEmitter *_particleEmitter) {
	particleEmitter = _particleEmitter;
}

void Enemy::collide(Object *ob) {
	if (ob->getType() == OType::OMeteor) {
		position = ob->getPos() + (position - ob->getPos()).normalized()*(ob->getRadius()+radius);
		flee(ob->getPos(), meteorFleeDistance, meteorMaxFleeDistance, meteorMaxSteering, ob->getRadius());
	}
	else if (ob->getType() == OType::OMissile) {
		healthPoints -= 1;
	}
}

void Enemy::seek(Vec3 target) {
	Vec3 desired = target - position;
	float distance = desired.length();
	if (distance > approachZone) {
		desired = desired.normalized() * maxDesired;
	}
	else {
		float desiredMag = (maxDesired * distance) / approachZone;
		desired = desired.normalized() * desiredMag;
	}
	Vec3 steering = desired - velocity;
	if (steering.length() > maxSteering) {
		steering = steering.normalized() * maxSteering;
	}

	velocity -= steering;
	//std::cout << "Velocity: " << velocity << std::endl;
	//std::cout << "Steering: " << steering << std::endl;
}

void Enemy::flee(Vec3 targetPos, float fleeDistance, float maxFleeDistance, float maxSteering, float targetRadius) {
	Vec3 desired = position - targetPos;
	float distance = desired.length() - targetRadius - radius;
	if (distance < 0) {
		distance = 0;
	}
	if (distance > fleeDistance) {
		return;
	}
	else if (distance <= maxFleeDistance) {
		desired = desired.normalized() * maxDesired;
	}
	else {
		float desiredMag = (maxDesired * (distance-maxFleeDistance)) / (fleeDistance - maxFleeDistance);
		desiredMag = maxDesired - desiredMag;
		desired = desired.normalized() * desiredMag;
	}
	Vec3 steering = desired - velocity;
	if (steering.length() > maxSteering) {
		steering = steering.normalized() * maxSteering;
	}
	velocity += steering;
}

void Enemy::respawn() {
	position = Vec3::random(-seekArea, seekArea);
	velocity = Vec3(0.01f, 0.00000f, 0);
	healthPoints = maxHealthPoints;
	currentScore = maxScore;
	frameCounter = 1;
}