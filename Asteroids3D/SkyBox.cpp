#include "SkyBox.h"



SkyBox::SkyBox(Object &_target, Model3D *_model, Texture2D *_texture, float _scale)
	: type(OType::OSkyBox)
	, target(_target)
	, scale(_scale)
	, model(_model)
	, texture(_texture)
{
}


SkyBox::~SkyBox()
{
}

int SkyBox::update() {
	return 0;
}
void SkyBox::render() {
	if (model) {
		glPushMatrix();
		Vec3 position = target.getPos();
		glTranslatef(position.x, position.y, position.z);  // Move right and into the screen
		glScalef(scale, scale, scale);

		float mAmb[4] = { 1.f, 1.f, 1.f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mAmb);
		
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
	}
}
Vec3 SkyBox::getPos() {
	return target.getPos();
}
Vec3 SkyBox::getDir() {
	return Vec3(0,0,-1);
}
Vec3 SkyBox::getUp() {
	return Vec3(0, 1, 0);
}
float SkyBox::getRadius() {
	return scale;
}
OType SkyBox::getType() {
	return type;
}