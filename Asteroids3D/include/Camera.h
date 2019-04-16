#pragma once
#include <GL/freeglut.h>
#include "Vec3.h"
#include "Object.h"
#include "CameraTarget.h"
#include "Player.h"
enum CameraState {
	FirstPerson,
	ThirdPerson
};

class Camera
{
public:
	Camera(Object *);
	~Camera();
	void update();
	void apply();
	void lookUpdate();

	void handleMouseMove(int, int, float, float);

	void setTarget(Object *);
	void setState(CameraState);
	
	void changeFixCamera();
	void changeScroll(bool);

	Object *getTarget();
	CameraState getState();
	Vec3 getPos();
	Vec3 getDir();
	Vec3 getUp();
	
private:
	Object *target;
	float scroll;
	Vec3 position;
	Vec3 direction;
	Vec3 up;

	CameraState state;

	int mouseLockTicks;
	
	int refreshTicks;
	float fixingVelocity;
	float scrollVelocity;
	float maxScroll;
	float thrustFactor;
	bool fixCamera;

};

