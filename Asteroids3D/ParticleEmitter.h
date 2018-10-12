#pragma once
#include "Object.h"
#include <vector>

class Camera;

class ParticleEmitter :
	public Object
{
public:
	enum Preset {
		PMeteorHitDust,
		PMeteorDestroyDust,
		PEnemyHitDust,
		PEnemyDestroyDust,
		PStarfighterEngine
	};

	struct Particle {
		Vec3 position;
		Vec3 velocity;
		Vec3 color;
		unsigned int lifeTime;
		unsigned int maxLifeTime;
	};
	struct Vertex {
		GLfloat position[3];
		GLfloat color[4];
	};

	ParticleEmitter(Camera *, Vec3, float, unsigned int, unsigned int, unsigned int, unsigned int, float, float, Vec3, float, float, bool = true, Vec3 = Vec3(0, 0, 0), bool = true);
	ParticleEmitter(Camera *, Vec3, Preset, Vec3=Vec3(0,0,0), float=1.f);
	~ParticleEmitter();

	int update();
	void render();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	float getRadius();
	OType getType();

	unsigned int getMaxParticles();

	void setPos(Vec3);
	void setVel(Vec3);

	bool isDead();

	void die();
	void overrideParticleVelocity(Vec3);
	void pushParticles(Vec3);

private:
	void initializeParticle(Particle &);
	void generateVertexBuffer();
	Vec3 applyMatrix(Vec3, float*);

	Camera *camera;
	Vec3 position;
	Vec3 velocity;
	
	std::vector<Vertex> vertexBuffer;
	std::vector<Particle> particles;

	float scale;
	unsigned int maxParticles;
	unsigned int maxLifeTime;
	unsigned int maxLifeTimeDeviation;
	unsigned int particlesPerUpdate;
	float velocityMag;
	float velocityMagDeviation;
	Vec3 color;
	float colorDeviation;

	float spawnRange;

	unsigned int deadParticles;
	bool dead;
	bool dieRequest;

	bool respawnParticles;
	bool applyEmiterVelocityToParticles;

	Vec3 particleVelocityOverride;
	Vec3 globalPush;
};

