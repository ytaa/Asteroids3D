#include "Player.h"
#include "PlayerTarget.h"
#include "Scene.h"
#include "Missile.h"
#include <cstdlib>
#include "ParticleEmitter.h"


Player::Player(Scene *_scene, GMode _gameMode, Model3D *_model, Texture2D *_texture, Light *_engineLightNear, Light *_engineLightFar, Vec3 _pos)
	: position(_pos)
	, direction(Vec3(0,0,1))
	, up(Vec3(0,1,0))
	, left(Vec3(-1,0,0))
	, radius(3.7f)
	, scale(0.03f)//0.03f
	, rotationVelocity(Vec3(0, 0, 0.001f))
	, rotationAcceleration(Vec3(0.0025f, 0.0015f, 0.0025f))
	, rotationDeacceleration(Vec3(0.90f, 0.86f, 0.90f))
	, rotationMaxVelocity(Vec3(0.03f, 0.03f, 0.035f))
	, rotationEnableFlag(Vec3(0,0,0))
	, thrustVelocity(0.001f)
	, thrustAcceleration(0.015f)
	, thrustDeacceleration(0.995f)
	, thrustMaxVelocity(1.75f)
	, thrustEnableFlag(0)
	, dragVelocity(0.f)
	, dragAcceleration(0.0025f)
	, dragDeacceleration(0.99f)
	, dragMaxVelocity(0.05f)
	, dragEnableFlag(0)
	, rotationMatrix(new float[16])
	, pitchMatrix(new float[16])
	, rollMatrix(new float[16])
	, yawMatrix(new float[16])
	, engineLightNear(_engineLightNear)
	, engineLightFar(_engineLightFar)
	, model(_model)
	, texture(_texture)
	, materialAmbient{ 0.085f, 0.085f, 0.085f, 1.0f }
	, materialDiffuse{ 0.17f, 0.17f, 0.17f, 1.0f }
	//, materialDiffuse{ 0.0f, 0.0f, 0.0f, 1.0f }
	, materialSpecular{ 0.45f, 0.45f, 0.45f, 1.0f }
	, shininess(7.f)
	, maxHealthPoints(3)
	, healthPoints(maxHealthPoints)
	, score(0)
	, maxInviolabilityTicks(60*3)
	, inviolabilityTicks(maxInviolabilityTicks)
	, missiles(std::vector<Missile *>())
	, missileFireVelocity(1.5f)
	, missileFireRate(10)
	, missileFireTicks(0)
	, gameMode(_gameMode)
	, timeLeft(23)
	, scene(_scene)
	, type(OType::OPlayer)
{
	//base modelview matrix
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (col == row)
				rotationMatrix[row+4*col] = 1.f;
			else
				rotationMatrix[row + 4 * col] = 0.f;
		}
	}
	//pitchMatrix
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (col == row)
				pitchMatrix[row + 4 * col] = 1.f;
			else
				pitchMatrix[row + 4 * col] = 0.f;
		}
	}
	//rollMatrix
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (col == row)
				rollMatrix[row + 4 * col] = 1.f;
			else
				rollMatrix[row + 4 * col] = 0.f;
		}
	}
	//yawMatrix
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (col == row)
				yawMatrix[row + 4 * col] = 1.f;
			else
				yawMatrix[row + 4 * col] = 0.f;
		}
	}

}

Player::~Player()
{
	delete[] rotationMatrix;
	delete[] pitchMatrix;
	delete[] rollMatrix;
	delete[] yawMatrix;
	for (unsigned int i = 0; i < missiles.size(); i++) {
		delete missiles[i];
	}

}

int Player::update() {
	//(de)accelerate pitch
	if (rotationEnableFlag.x == 0) {
		rotationVelocity.x *= rotationDeacceleration.x;
	}
	else if (rotationEnableFlag.x == 1) {
		if (rotationVelocity.x < 0)
		rotationVelocity.x = rotationVelocity.x*rotationDeacceleration.x;
		if (fabs(rotationVelocity.x + rotationAcceleration.x) < fabs(rotationMaxVelocity.x))
		rotationVelocity.x += rotationAcceleration.x;
	}
	else {
		if (rotationVelocity.x > 0)
		rotationVelocity.x = rotationVelocity.x*rotationDeacceleration.x;
		if (fabs(rotationVelocity.x - rotationAcceleration.x) < fabs(rotationMaxVelocity.x))
		rotationVelocity.x -= rotationAcceleration.x;
	}
	applyPitch();
	//(de)accelerate yaw
	if (rotationEnableFlag.y == 0) {
		rotationVelocity.y *= rotationDeacceleration.y;
	}
	else if (rotationEnableFlag.y == 1) {
		if (rotationVelocity.y < 0)
			rotationVelocity.y = rotationVelocity.y*rotationDeacceleration.y;
		if (fabs(rotationVelocity.y + rotationAcceleration.y) < fabs(rotationMaxVelocity.y))
			rotationVelocity.y += rotationAcceleration.y;
	}
	else {
		if (rotationVelocity.y > 0)
			rotationVelocity.y = rotationVelocity.y*rotationDeacceleration.y;
		if (fabs(rotationVelocity.y - rotationAcceleration.y) < fabs(rotationMaxVelocity.y))
			rotationVelocity.y -= rotationAcceleration.y;
	}
	applyYaw();
	//(de)accelerate roll
	if (rotationEnableFlag.z == 0) {
		rotationVelocity.z *= rotationDeacceleration.z;
	}
	else if (rotationEnableFlag.z == 1) {
		if (rotationVelocity.z < 0)
			rotationVelocity.z = rotationVelocity.z*rotationDeacceleration.z;
		if (fabs(rotationVelocity.z + rotationAcceleration.z) < fabs(rotationMaxVelocity.z))
			rotationVelocity.z += rotationAcceleration.z;
	}
	else {
		if (rotationVelocity.z > 0)
			rotationVelocity.z = rotationVelocity.z*rotationDeacceleration.z;
		if (fabs(rotationVelocity.z - rotationAcceleration.z) < fabs(rotationMaxVelocity.z))
			rotationVelocity.z -= rotationAcceleration.z;
	}
	applyRoll();
	rotationEnableFlag = Vec3(0, 0, 0);

	//(de)accelerate thrust
	if(thrustEnableFlag == 0){
		thrustVelocity *= thrustDeacceleration;
	}
	else {
		if (thrustVelocity < thrustMaxVelocity) {
			thrustVelocity += thrustAcceleration;
		}
		thrustEnableFlag = 0;
	}
	//(de)accelerate drag
	if (dragEnableFlag == 0) {
		dragVelocity *= dragDeacceleration;
	}
	else {
		if (dragVelocity < dragMaxVelocity) {
			dragVelocity += dragAcceleration;
		}
		dragEnableFlag = 0;
	}

	//apply thrust
	position += direction*thrustVelocity;
	//apply drag
	position -= direction*dragVelocity;

	//set dir up and left from rotationMatrix
	direction.x = rotationMatrix[8];
	direction.y = rotationMatrix[9];
	direction.z = rotationMatrix[10];
	direction = direction.normalized();
	up.x = rotationMatrix[4];
	up.y = rotationMatrix[5];
	up.z = rotationMatrix[6];
	up = up.normalized();
	left.x = rotationMatrix[0];
	left.y = rotationMatrix[1];
	left.z = rotationMatrix[2];
	left = left.normalized();


	//update lights
	if (engineLightNear) {
		Vec3 lightNearPosVec = position - (direction - up*0.25) * radius*0.5;
		engineLightNear->setPos(lightNearPosVec);
	}
	if (engineLightFar) {
		Vec3 lightFarPosVec = position - ((direction - up*0.1f) * (radius*1.4f));
		engineLightFar->setPos(lightFarPosVec);
	}

	if (inviolabilityTicks > 0)
		inviolabilityTicks--;

	//free missiles with passed lifetime
	for (unsigned int i = 0; i < missiles.size(); i++) {	
		if (missiles[i]->isReadyToBeDeleted()) {
			Missile* missile = missiles[i];
			missiles.erase(missiles.begin() + i);
			delete missile;
			i--;
		}
	}
	//update missileFireTicks
	if(missileFireTicks > 0)
		missileFireTicks--;

		
	//system("cls");
	//std::cout << position << std::endl;

	return 0;
}

void Player::render() {
	if (inviolabilityTicks > 0) {
		unsigned int ticks = inviolabilityTicks % 60;
		if (ticks < 30)
			return;
	}
	if (model) {
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);  // Move right and into the screen
		glMultMatrixf(rotationMatrix);
		glScalef(scale, scale, scale);
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
		glPopMatrix();

		
		
		/*
		std::vector<Vec3> points = getBoundaryPoints();
		for (unsigned int i = 0; i < points.size(); i++) {
			glPushMatrix();
			glTranslatef(points[i].x, points[i].y, points[i].z);
			glutSolidSphere(0.3, 20, 20);
			glPopMatrix();
		}*/
	}
}

Vec3 Player::getPos() {
	return position;
}
Vec3 Player::getDir() {
	return direction;
}
Vec3 Player::getUp() {
	return up;
}
float Player::getThrust() {
	return thrustVelocity;
}
float Player::getRadius() {
	return radius;
}
int Player::getMaxHP() {
	return maxHealthPoints;
}
int Player::getHP() {
	return healthPoints;
}
unsigned int Player::getScore() {
	return score;
}
OType Player::getType() {
	return type;
}
int Player::getTimeLeft() {
	return timeLeft;
}
GMode Player::getGameMode() {
	return gameMode;
}

void Player::changePitch(bool dir) {
	// x axis rotation

	if (dir) {
		rotationEnableFlag.x = 1;
	}
	else {
		rotationEnableFlag.x = -1;
	}
}
void Player::changeYaw(bool dir){
	// y axis rotation
	
	if (dir) {
		rotationEnableFlag.y = 1;
	}
	else {
		rotationEnableFlag.y = -1;
	}
}
void Player::changeRoll(bool dir) {
	// z axis rotation
	if (dir) {
		rotationEnableFlag.z = 1;
	}
	else {
		rotationEnableFlag.z = -1;
	}
}
void Player::changeThrust() {
	thrustEnableFlag = 1;
}
void Player::changeDrag() {
	dragEnableFlag = 1;
}

void Player::applyPitch() {
	GLfloat theta = rotationVelocity.x;
	pitchMatrix[5] = cos(theta);
	pitchMatrix[9] = -sin(theta);
	pitchMatrix[6] = sin(theta);
	pitchMatrix[10] = cos(theta);
	GLfloat *ans = matrixMultiplcation(rotationMatrix, pitchMatrix);
	delete[] rotationMatrix;
	rotationMatrix = ans;
}
void Player::applyYaw() {
	GLfloat theta = rotationVelocity.y;
	yawMatrix[0] = cos(theta);
	yawMatrix[8] = sin(theta);
	yawMatrix[2] = -sin(theta);
	yawMatrix[10] = cos(theta);
	GLfloat *ans = matrixMultiplcation(rotationMatrix, yawMatrix);
	delete[] rotationMatrix;
	rotationMatrix = ans;
}
void Player::applyRoll() {
	GLfloat theta = rotationVelocity.z;
	rollMatrix[0] = cos(theta);
	rollMatrix[4] = -sin(theta);
	rollMatrix[1] = sin(theta);
	rollMatrix[5] = cos(theta);
	GLfloat *ans = matrixMultiplcation(rotationMatrix, rollMatrix);
	delete[] rotationMatrix;
	rotationMatrix = ans;
}

GLfloat *Player::matrixMultiplcation(GLfloat *m1, GLfloat *m2) {
	GLfloat *ans = new GLfloat[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0.f;
			for (int k = 0; k < 4; k++) {
				sum += m1[i+4*k]*m2[k+4*j];
			}
			ans[i + 4 * j] = sum;
		}
	}
	return ans;
}

void Player::setLights(Light* _enginLightNear, Light *_engineLightFar) {
	engineLightNear = _enginLightNear;
	engineLightFar = _engineLightFar;
}
void Player::setScore(unsigned int _score) {
	score = _score;
}

void Player::setMaxHp(int _maxHP) {
	maxHealthPoints = _maxHP;
	healthPoints = maxHealthPoints;
}
void Player::setTimeLeft(int _timeLeft) {
	timeLeft = _timeLeft;
}

std::vector<Vec3> Player::getBoundaryPoints() {
	std::vector<Vec3> points;
	points.push_back(position-direction*radius*0.5f);
	points.push_back(position - direction*radius*0.5f + left*radius*0.6f);
	points.push_back(position - direction*radius*0.5f - left*radius*0.6f);
	points.push_back(position - direction*radius*0.5f + up*radius*0.4f);
	points.push_back(position + direction*radius);
	return points;
}

bool Player::isInviolable() {
	if (inviolabilityTicks > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::fireMissile() {
	//scene->addObject(new ParticleEmitter(scene->getCamera(), Vec3(0,0,100), 1.f, 2000, 30, 10, 0.5f, 0.15f, Vec3(0.65f, 0.15f, 0.15f), 0.15f));
	if (missileFireTicks == 0) {
		Vec3 pos1 = position + left*radius*0.28f + direction*radius*0.8f + up*radius*0.05f;
		Vec3 pos2 = position - left*radius*0.28f + direction*radius*0.8f + up*radius*0.05f;
		Vec3 vel = direction*thrustVelocity + direction*missileFireVelocity + up*rotationVelocity.x*(-20.f) + left*rotationVelocity.y*20.f;
		missiles.push_back(new Missile(this, pos1, vel));
		scene->addObject(missiles[missiles.size() - 1]);
		missiles.push_back(new Missile(this, pos2, vel));
		scene->addObject(missiles[missiles.size() - 1]);
		missileFireTicks = missileFireRate;
	}
}

void Player::collide(Object *obj) {
	if (obj->getType() == OType::OMeteor) {
		inviolabilityTicks = maxInviolabilityTicks;
		healthPoints -= 1;
	}
	else if (obj->getType() == OType::OPlayerTarget) {
		//score += ((PlayerTarget*)obj)->getScore();
	}
}