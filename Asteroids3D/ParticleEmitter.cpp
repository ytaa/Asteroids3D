#include "ParticleEmitter.h"
#include "Camera.h"


ParticleEmitter::ParticleEmitter(Camera *_camera, Vec3 _pos, float _scale, unsigned int _maxParticles, unsigned int _maxLifeTime, unsigned int _lifeTimeDeviation, unsigned int _particlesPerUpdate,
								 float _velocityMag, float _velocityMagDeviation, Vec3 _color, float _colorDeviation, float _spawnRange, bool _respawnParticles, Vec3 _velocity, bool _applyEmiterVelocityToParticles) //kupsko z dupska
	: camera(_camera)
	, position(_pos)
	, velocity(_velocity)
	, vertexBuffer(std::vector<Vertex>())
	, particles(std::vector<Particle>())
	, scale(_scale)
	, maxParticles(_maxParticles)
	, maxLifeTime(_maxLifeTime)
	, maxLifeTimeDeviation(_lifeTimeDeviation)
	, particlesPerUpdate(_particlesPerUpdate)
	, velocityMag(_velocityMag)
	, velocityMagDeviation(_velocityMagDeviation)
	, color(_color)
	, colorDeviation(_colorDeviation)
	, spawnRange(_spawnRange)
	, deadParticles(0)
	, dead(false)
	, dieRequest(false)
	, respawnParticles(_respawnParticles)
	, applyEmiterVelocityToParticles(_applyEmiterVelocityToParticles)
	, particleVelocityOverride(Vec3(0, 0, 0))
	, globalPush(Vec3(0, 0, 0))
{
}

ParticleEmitter::ParticleEmitter(Camera *_camera, Vec3 _position, Preset preset, Vec3 _velocity, float _scale)
	: camera(_camera)
	, position(_position)
	, velocity(_velocity) 
	, vertexBuffer(std::vector<Vertex>())
	, particles(std::vector<Particle>())
	, deadParticles(0)
	, dead(false)
	, dieRequest(false)
	, particleVelocityOverride(Vec3(0, 0, 0))
	, globalPush(Vec3(0, 0, 0))
{
	if (preset == PMeteorHitDust) {
		scale = 0.1f;
		maxParticles = 900;
		maxLifeTime = 30;
		maxLifeTimeDeviation = 5;
		particlesPerUpdate = 300;
		velocityMag = 0.15f;
		velocityMagDeviation = 0.05f;
		color = Vec3(0.25f, 0.25f, 0.25f);
		colorDeviation = 0.15f;
		spawnRange = 0.f;
		respawnParticles = false;
		applyEmiterVelocityToParticles = true;
	}
	else if (preset == PMeteorDestroyDust) {
		scale = _scale/30.f;
		maxParticles = 2500;
		maxLifeTime = 120;
		maxLifeTimeDeviation = 5;
		particlesPerUpdate = maxParticles;
		velocityMag = 0.30f;
		velocityMagDeviation = 0.10f;
		color = Vec3(0.2f, 0.2f, 0.2f);
		colorDeviation = 0.15f;
		spawnRange = _scale*1.1f;
		respawnParticles = false;
		applyEmiterVelocityToParticles = true;
	}
	else if (preset == PEnemyHitDust) {
		scale = 0.05f;
		maxParticles = 500;
		maxLifeTime = 30;
		maxLifeTimeDeviation = 2;
		particlesPerUpdate = 200;
		velocityMag = 0.20f;
		velocityMagDeviation = 0.05f;
		//color = Vec3(0.55f, 0.55f, 0.25f);
		color = Vec3(0.7f, 0.7f, 0.9f);
		colorDeviation = 0.15f;
		spawnRange = 0.f;
		respawnParticles = false;
		applyEmiterVelocityToParticles = true;
	}
	else if (preset == PEnemyDestroyDust) {
		scale = _scale / 30.f;
		maxParticles = 2500;
		maxLifeTime = 120;
		maxLifeTimeDeviation = 5;
		particlesPerUpdate = maxParticles/4;
		velocityMag = 0.30f;
		velocityMagDeviation = 0.10f;
		color = Vec3(0.6f, 0.6f, 0.9f);
		colorDeviation = 0.15f;
		spawnRange = _scale*1.1f;
		respawnParticles = false;
		applyEmiterVelocityToParticles = true;
	}
	else if (preset == PStarfighterEngine) {
		scale = 0.05f;
		maxParticles = 10000;
		maxLifeTime = 10;
		maxLifeTimeDeviation = 2;
		particlesPerUpdate = maxParticles/maxLifeTime;
		velocityMag = 0.05f;
		velocityMagDeviation = 0.05f;
		color = Vec3(0.45f, 0.05f, 0.05f);
		colorDeviation = 0.15f;
		spawnRange = 0.5f;
		respawnParticles = true;
		applyEmiterVelocityToParticles = true;
	}
}

ParticleEmitter::~ParticleEmitter()
{
	
}

int ParticleEmitter::update() {
	position += velocity;

	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].position += particles[i].velocity;
		particles[i].position += globalPush;
		if(applyEmiterVelocityToParticles)
			particles[i].position += velocity;
		if(particles[i].lifeTime>0)
			particles[i].lifeTime--;
		if (particles[i].lifeTime == 0) {
			if(respawnParticles)
				initializeParticle(particles[i]);
			else
				deadParticles++;
		}
	}
	if (deadParticles >= maxParticles || dieRequest == true) {
		dead = true;
		return -1;
	}
	unsigned int j = 0;
	while (j<particlesPerUpdate && particles.size() < maxParticles) {
		Particle p;
		initializeParticle(p);
		particles.push_back(p);
		j++;
	}
	generateVertexBuffer();
	particleVelocityOverride = Vec3(0, 0, 0);
	globalPush = Vec3(0, 0, 0);
	return 0;
}
void ParticleEmitter::render() {
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(vertexBuffer[0].position));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(vertexBuffer[0].color));

	glDrawArrays(GL_QUADS, 0, vertexBuffer.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	glPopMatrix();
}
Vec3 ParticleEmitter::getPos() {
	return position;
}
Vec3 ParticleEmitter::getDir() {
	return (position - camera->getPos()).normalized();
}
Vec3 ParticleEmitter::getUp() {
	return camera->getUp();
}
float ParticleEmitter::getRadius() {
	return 1.f;
}
OType ParticleEmitter::getType() {
	return OType::OParticleEmitter;
}

unsigned int ParticleEmitter::getMaxParticles() {
	return maxParticles;
}

void ParticleEmitter::setPos(Vec3 _position) {
	position = _position;
}

void ParticleEmitter::setVel(Vec3 _velocity) {
	velocity = _velocity;
}


void ParticleEmitter::initializeParticle(Particle &p) {
	p.position = position + Vec3::random(-1, 1).normalized()*rng::rand(0.f, spawnRange);
	if (particleVelocityOverride == Vec3(0, 0, 0)){
		p.velocity = Vec3::random(-1.f, 1.f).normalized()*(velocityMag + rng::rand(-velocityMagDeviation, velocityMagDeviation));
	}
	else {
		p.velocity = particleVelocityOverride*(velocityMag + rng::rand(-velocityMagDeviation, velocityMagDeviation));
	}
	p.color = color+rng::rand(-colorDeviation,colorDeviation);
	p.maxLifeTime = maxLifeTime + rng::rand(-(int)maxLifeTimeDeviation, (int)maxLifeTimeDeviation);
	p.lifeTime = p.maxLifeTime;
}
void ParticleEmitter::generateVertexBuffer() {
	vertexBuffer.resize(particles.size()*4);

	Vec3 z = position - camera->getPos();
	Vec3 x = camera->getUp().cross(z); //Vec3(0, 1, 0).cross(x)
	Vec3 y = z.cross(x);

	x = x.normalized()*scale;
	y = y.normalized()*scale;
	z = z.normalized()*scale;

	float matrix[16];

	matrix[0] = x.x; 
	matrix[1] = x.y;
	matrix[2] = x.z;
	matrix[3] = 0;

	matrix[4] = y.x;
	matrix[5] = y.y;
	matrix[6] = y.z;
	matrix[7] = 0;

	matrix[8] = z.x;
	matrix[9] = z.y;
	matrix[10] = z.z;
	matrix[11] = 0;

	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;

	
	for (unsigned int i = 0; i < particles.size(); i++) {
		matrix[12] = particles[i].position.x;
		matrix[13] = particles[i].position.y;
		matrix[14] = particles[i].position.z;
		Vec3 v1 = applyMatrix(Vec3(0, 0, 0), matrix);
		Vec3 v2 = applyMatrix(Vec3(0, 1, 0), matrix);
		Vec3 v3 = applyMatrix(Vec3(1, 1, 0), matrix);
		Vec3 v4 = applyMatrix(Vec3(1, 0, 0), matrix);
		for (int j = 0; j < 4; j++) {
			Vec3 v;
			if (j == 0)
				v = v1;
			else if (j == 1)
				v = v2;
			else if (j == 2)
				v = v3;
			else
				v = v4;
			Vertex vr;
			vr.position[0] = v.x;
			vr.position[1] = v.y;
			vr.position[2] = v.z;
			vr.color[0] = particles[i].color.x;
			vr.color[1] = particles[i].color.y;
			vr.color[2] = particles[i].color.z;
			vr.color[3] = (GLfloat)particles[i].lifeTime/particles[i].maxLifeTime;
			//vr.color[3] = 1;
			if (vr.color[3] < 0.25f) {
				vr.color[3] = 0.25f;
			}
			vertexBuffer[i * 4 + j] = vr;
		}
	}

}

Vec3 ParticleEmitter::applyMatrix(Vec3 v, float* m) {
	Vec3 rv;
	rv.x = v.x*m[0] + v.y*m[4] + v.z*m[8] + m[12];
	rv.y = v.x*m[1] + v.y*m[5] + v.z*m[9] + m[13];
	rv.z = v.x*m[2] + v.y*m[6] + v.z*m[10] + m[14];
	return rv;
}

bool ParticleEmitter::isDead() {
	return dead;
}

void ParticleEmitter::die() {
	dieRequest = true;
}

void ParticleEmitter::overrideParticleVelocity(Vec3 _ovel) {
	particleVelocityOverride = _ovel;
}
void ParticleEmitter::pushParticles(Vec3 _gpush) {
	globalPush = _gpush;
}