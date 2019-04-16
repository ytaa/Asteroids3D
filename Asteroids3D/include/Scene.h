#pragma once
#include <vector>
#include <GL/freeglut.h>
#include <windows.h> 
#include <cmath>
#include <vector>
#include "Object.h"
#include "Light.h"



class Camera;
class HudController;
class CollisionHandler;

class Scene {
public:
	Scene(Camera * = NULL, HudController * = NULL);
	~Scene();
	void update();
	void render();
	unsigned int addObject(Object*);
	void eraseObject(unsigned int);

	Light * getLight(unsigned int);
	unsigned int getObjectsNumber();
	Camera * getCamera();

	void setCamera(Camera *);
	void setHud(HudController *);

private:
	Camera *camera;
	HudController *hud;
	std::vector<Light*> lights;
	std::vector<Object*> objects;
	CollisionHandler* collisionHandler;
};