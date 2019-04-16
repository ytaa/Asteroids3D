#include "CollisionHandler.h"
#include "Scene.h"


CollisionHandler::CollisionHandler(Scene *_scene, std::vector<Object *> *_objects)
	:scene(_scene)
	,objects(_objects)
{
}


CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::update() {
	for (unsigned int i = 0; i < objects->size()-1; i++) {
		for (unsigned int j = i+1; j < objects->size(); j++) {
			float distance = (*objects)[i]->getPos().distance((*objects)[j]->getPos());
			if (distance < (*objects)[i]->getRadius() + (*objects)[j]->getRadius()) {
				collide((*objects)[i], (*objects)[j]);
			}
		}
	}
}

void CollisionHandler::collide(Object *ob1, Object *ob2) {
	
	if (ob1->getType() == OType::OPlayer && ob2->getType() == OType::OMeteor ||
		ob2->getType() == OType::OPlayer && ob1->getType() == OType::OMeteor) {
		Player *player;
		Meteor *meteor;
		if (ob1->getType() == OType::OPlayer) {
			player = (Player*)ob1;
			meteor = (Meteor*)ob2;
		}
		else {
			meteor = (Meteor*)ob1;
			player = (Player*)ob2;
		}
		if (!player->isInviolable()) {
			if (meteor->getHp() > 0) {
				std::vector<Vec3> boundaryPoints = player->getBoundaryPoints();
				for (unsigned int i = 0; i < boundaryPoints.size(); i++) {
					if (meteor->getPos().distance(boundaryPoints[i]) < meteor->getRadius()) {
						player->collide(meteor);
						break;
					}
				}
			}
		}
	}
	else if (ob1->getType() == OType::OPlayer && ob2->getType() == OType::OPlayerTarget ||
			 ob2->getType() == OType::OPlayer && ob1->getType() == OType::OPlayerTarget) {
		Player *player;
		PlayerTarget *playerTarget;
		if (ob1->getType() == OType::OPlayer) {
			player = (Player*)ob1;
			playerTarget = (PlayerTarget*)ob2;
		}
		else {
			playerTarget = (PlayerTarget*)ob1;
			player = (Player*)ob2;
		}
		player->collide(playerTarget);
		playerTarget->respawn();
	}
	else if (ob1->getType() == OType::OMeteor && ob2->getType() == OType::OMeteor) {
		Meteor *m1 = (Meteor*)ob1;
		Meteor *m2 = (Meteor*)ob2;
		if (m1->getHp() <= 0)
			return;
		if (m2->getHp() <= 0)
			return;
		applyElasticCollision(m1, m2);
		if (m1->getVel().length() > Meteor::maxVelocity) {
			m1->setVel(m1->getVel().normalized()*Meteor::maxVelocity);
		}
		if (m2->getVel().length() > Meteor::maxVelocity) {
			m2->setVel(m2->getVel().normalized()*Meteor::maxVelocity);
		}
	}
	else if (ob1->getType() == OType::OMissile && ob2->getType() == OType::OMeteor ||
		ob2->getType() == OType::OMissile && ob1->getType() == OType::OMeteor) {
		Missile *missile;
		Meteor *meteor;
		if (ob1->getType() == OType::OMissile) {
			missile = (Missile*)ob1;
			meteor = (Meteor*)ob2;
		}
		else {
			meteor = (Meteor*)ob1;
			missile = (Missile*)ob2;
		}
		if (missile->isHit())
			return;
		if (meteor->getHp() <= 0)
			return;
		Vec3 pePos = meteor->getPos() + ((missile->getPos() - meteor->getPos()).normalized()*(meteor->getRadius()+0.2f));
		ParticleEmitter *pe = new ParticleEmitter(scene->getCamera(), pePos, ParticleEmitter::PMeteorHitDust, meteor->getVel());

		scene->addObject(pe);
		missile->collide(pe);
		meteor->collide(missile);
		if (meteor->getHp() <= 0) {
			ParticleEmitter *meteorPe = new ParticleEmitter(scene->getCamera(), meteor->getPos(), ParticleEmitter::PMeteorDestroyDust, meteor->getVel(), meteor->getRadius());
			scene->addObject(meteorPe);
			meteor->setParticleEmitter(meteorPe);
		}
	}
	else if (ob1->getType() == OType::OMissile && ob2->getType() == OType::OEnemy ||
		ob2->getType() == OType::OMissile && ob1->getType() == OType::OEnemy) {
		Missile *missile;
		Enemy *enemy;
		if (ob1->getType() == OType::OMissile) {
			missile = (Missile*)ob1;
			enemy = (Enemy*)ob2;
		}
		else {
			enemy = (Enemy*)ob1;
			missile = (Missile*)ob2;
		}
		if (missile->isHit())
			return;
		if (enemy->getHp() <= 0)
			return;
		Vec3 pePos = enemy->getPos() + ((missile->getPos() - enemy->getPos()).normalized()*(enemy->getRadius() + 0.2f));
		ParticleEmitter *pe = new ParticleEmitter(scene->getCamera(), pePos, ParticleEmitter::PEnemyHitDust, enemy->getVel());

		scene->addObject(pe);
		missile->collide(pe);
		enemy->collide(missile);
		if (enemy->getHp() <= 0) {
			ParticleEmitter *pe = new ParticleEmitter(scene->getCamera(), enemy->getPos(), ParticleEmitter::PEnemyDestroyDust, enemy->getVel(), enemy->getRadius());
			scene->addObject(pe);
			enemy->setParticleEmitter(pe);
		}
	}
	else if (ob1->getType() == OType::OEnemy && ob2->getType() == OType::OMeteor ||
		ob2->getType() == OType::OEnemy && ob1->getType() == OType::OMeteor) {
		Enemy *enemy;
		Meteor *meteor;
		if (ob1->getType() == OType::OEnemy) {
			enemy = (Enemy*)ob1;
			meteor = (Meteor*)ob2;
		}
		else {
			meteor = (Meteor*)ob1;
			enemy = (Enemy*)ob2;
		}
		enemy->collide(meteor);
	}
}
void CollisionHandler::applyElasticCollision(Meteor *ob1, Meteor *ob2) {
	using namespace std;
	//geting values from objects
	Vec3 pos1 = ob1->getPos();
	Vec3 v1 = ob1->getVel();
	//float m1 =ob1->getMass();
	float m1 = pow(ob1->getRadius(), 2);
	Vec3 pos2 = ob2->getPos();
	Vec3 v2 = ob2->getVel();
	//float m2 = ob2->getMass(); 
	float m2 = pow(ob2->getRadius(), 2);

	//Perfect elastic collision
	//x:
	float p = v1.x*m1 + v2.x * m2; //momentum
	float E = (m1*pow(v1.x, 2)) / 2 + (m2*pow(v2.x, 2)) / 2; //kinetic energy
	float a = m1 + pow(m1, 2) / m2;
	float b = -(2 * p*m1) / m2;
	float c = pow(p, 2) / m2 - (2 * E);
	float delta = b*b - 4 * a*c;
	if (delta < 0)
	{
		/*cout << "delta ujemna" << endl;
		cout << "obliczenia dla x" << endl;
		cout << "v1x=" << v1.x << " v2x=" << v2.x << endl << endl;*/
		delta = fabs(delta);
	}
	float root = sqrt(delta);
	if (pos2.x >= pos1.x) root = -root;
	v1.x = (-b + root) / (2 * a);
	v2.x = (p - m1*v1.x) / m2;

	//y:
	p = v1.y*m1 + v2.y * m2; //momentum
	E = (m1*pow(v1.y, 2)) / 2 + (m2*pow(v2.y, 2)) / 2; //kinetic energy
	a = m1 + pow(m1, 2) / m2;
	b = -(2 * p*m1) / m2;
	c = pow(p, 2) / m2 - (2 * E);
	delta = b*b - 4 * a*c;
	if (delta < 0)
	{
		/*cout << "delta ujemna" << endl;
		cout << "obliczenia dla y" << endl;
		cout << "v1y=" << v1.y << " v2y=" << v2.y << endl << endl;*/
		delta = fabs(delta);
	}
	root = sqrt(delta);
	if (pos2.y >= pos1.y) root = -root;
	v1.y = (-b + root) / (2 * a);
	v2.y = (p - m1*v1.y) / m2;

	//z:
	p = v1.z*m1 + v2.z * m2; //momentum
	E = (m1*pow(v1.z, 2)) / 2 + (m2*pow(v2.z, 2)) / 2; //kinetic energy
	a = m1 + pow(m1, 2) / m2;
	b = -(2 * p*m1) / m2;
	c = pow(p, 2) / m2 - (2 * E);
	delta = b*b - 4 * a*c;
	if (delta < 0)
	{
		/*cout << "delta ujemna" << endl;
		cout << "obliczenia dla z" << endl;
		cout << "v1z=" << v1.z << " v2z=" << v2.z << endl << endl;*/
		delta = fabs(delta);
	}
	root = sqrt(delta);
	if (pos2.z >= pos1.z) root = -root;
	v1.z = (-b + root) / (2 * a);
	v2.z = (p - m1*v1.z) / m2;

	//std::cout << v1.x << ", " << v1.y << std::endl;
	//std::cout << v2.x << ", " << v2.y << std::endl;

	ob1->setVel(v1);
	ob2->setVel(v2);
}