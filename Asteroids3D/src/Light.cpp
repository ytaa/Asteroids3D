#include "Light.h"



Light::Light(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 _position, float _type, int _attenuationType, float _attenuationFactor, float _cutoff, Vec3 _direction)
	: ambient(amb)
	, diffuse(diff)
	, specular(spec)
	, position(_position)
	, type(_type)
	, attenutaionType(_attenuationType)
	, attenuationFactor(_attenuationFactor)
	, cutoff(_cutoff)
	, direction(_direction)
	, enable(true)
{
	int i = 0;
	while (i < 8) {
		if (lightFlags[i] == false) {
			lightFlags[i] = true;
			lightHandle = GL_LIGHT0 + i;
			glEnable(lightHandle);
			float ambient[4] = { amb.x, amb.y, amb.z, 1.f };
			float diffuse[4] = { diff.x, diff.y, diff.z, 1.f };
			float specular[4] = { spec.x, spec.y, spec.z, 1.f };
			glLightfv(lightHandle, GL_AMBIENT, ambient);
			glLightfv(lightHandle, GL_DIFFUSE, diffuse);
			glLightfv(lightHandle, GL_SPECULAR, specular);
			if (attenutaionType != 0) {
				glLightf(lightHandle, attenutaionType, attenuationFactor);
			}
			break;
		}
		i++;
	}
	if (i < 8) {
		good = true;
	}
	else {
		good = false;
	}
}


Light::~Light()
{
	glDisable(lightHandle);
	lightFlags[lightHandle - GL_LIGHT0] = false;
}

void Light::render() {
	if (!enable)
		return;
	float pos[4] = { position.x, position.y, position.z, type };
	glLightfv(lightHandle, GL_POSITION, pos);
	if (cutoff != 0.f) {
		float lightDir[3] = { direction.x, direction.y, direction.z };
		glLightfv(lightHandle, GL_SPOT_DIRECTION, lightDir);
		glLightf(lightHandle, GL_SPOT_CUTOFF, cutoff);
	}
}
void Light::setPos(Vec3 _position) {
	if(good)
		position = _position;
}
void Light::setDir(Vec3 _dir) {
	if (good)
		direction = _dir;
}
void Light::setEnable(bool _enable) {
	enable = _enable;
}
bool Light::isGood() {
	return good;
}
void Light::changeBrightness(float factor) {
	ambient = ambient*factor;
	diffuse = diffuse*factor;
	specular = specular*factor;
	float ambientTab[4] = { ambient.x, ambient.y, ambient.z, 1.f };
	float diffuseTab[4] = { diffuse.x, diffuse.y, diffuse.z, 1.f };
	float specularTab[4] = { specular.x, specular.y, specular.z, 1.f };
	glLightfv(lightHandle, GL_AMBIENT, ambientTab);
	glLightfv(lightHandle, GL_DIFFUSE, diffuseTab);
	glLightfv(lightHandle, GL_SPECULAR, specularTab);

}

bool Light::lightFlags[8] = { 0,0,0,0,0,0,0,0 };
