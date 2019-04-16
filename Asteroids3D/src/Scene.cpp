#include "Scene.h"
#include "Camera.h"
#include "HudController.h"
#include "CollisionHandler.h"
Scene::Scene(Camera* _camera, HudController* _hud)
	:camera(_camera)
	,hud(_hud)
	,lights(std::vector<Light*>
		{ new Light(Vec3(1.f, 1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(1.0f, 0.0f, 0.0f), 0)
		, new Light(Vec3(1.f, 1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(1.f, 1.f, 1.f), Vec3(0.0f, 0.0f, 0.0f), 1.f, GL_QUADRATIC_ATTENUATION, 0.9f)
		, new Light(Vec3(1, 0, 0.f), Vec3(1.f, 0, 0.f), Vec3(1.f, 0, 0.f), Vec3(0.0f, 0.0f, 0.0f), 1.f, GL_QUADRATIC_ATTENUATION, 0.04f)
		, new Light(Vec3(0.25f, 0.25f, 0.7f), Vec3(0.25f, 0.25f, 0.7f), Vec3(0.25f, 0.25f, 0.7f), Vec3(0.0f, 0.0f, 0.0f), 1.f, GL_QUADRATIC_ATTENUATION, 0.005f)
        })
	,objects(std::vector<Object *>())
	,collisionHandler(new CollisionHandler(this, &objects))
{
}
Scene::~Scene(){
	for (unsigned int i = 0; i < lights.size(); i++) {
		delete lights[i];
	}
	delete collisionHandler;
}
unsigned int Scene::addObject(Object* obj) {
	objects.push_back(obj);
	return objects.size() - 1;
}
void Scene::eraseObject(unsigned int index) {
	if (index < objects.size()) {
		objects.erase(objects.begin() + index);
	}
}
void Scene::update(){
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->update() < 0) {
			objects.erase(objects.begin() + i);
			i--;
		}
	}
	collisionHandler->update();
	if(camera)
		camera->update();
	if(hud)
		hud->update();
}
void Scene::render(){
	//Sleep(1);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);    
	glLoadIdentity();  
	
	//camera
	if (camera) {
		camera->lookUpdate();
		camera->apply();
	}

	//lights
	for (unsigned int i = 0; i < lights.size(); i++) {
		lights[i]->render();
	}
	
	//objects
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->render();
	}

	//2D HUD 
	if(hud)
		hud->render();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	return;
}
unsigned int Scene::getObjectsNumber() {
	return objects.size();
}
Light* Scene::getLight(unsigned int ind) {
	return lights[ind];
}
Camera * Scene::getCamera() {
	return camera;
}
void Scene::setCamera(Camera *_camera) {
	camera = _camera;
}
void Scene::setHud(HudController *_hud) {
	hud = _hud;
}