#include "Camera.h"
#include <iostream>
Camera::Camera(Object *_target)
	:target(_target)
	,scroll(4.5f)
	,position(target->getPos() - (target->getDir() - target->getUp()*0.2f).normalized()*target->getRadius() * scroll)
	,direction((target->getPos() - position).normalized())
	,up(_target->getUp())
	,state(CameraState::ThirdPerson)
	,mouseLockTicks(0)
	,refreshTicks(150)
	,fixingVelocity(0.05f)
	,scrollVelocity(0.2f)
	,maxScroll(7.5f)
	,thrustFactor(2.5f)
	,fixCamera(true)
{
}


Camera::~Camera()
{
}

void Camera::lookUpdate() {
	if (state == ThirdPerson) {
		direction = target->getPos() - position;
		direction = direction.normalized();
		position = target->getPos() - direction * (target->getRadius() * scroll);
		if (target->getType() == OType::OPlayer) {
			Player *target = (Player *)this->target;
			position = position - direction*(target->getRadius()*target->getThrust()*thrustFactor);
		}
	}
}

void Camera::update() {
	//std::cout << (target).position << target.direction << target.up << std::endl;
	if (state == CameraState::FirstPerson) {
		position = target->getPos() + (target->getDir()*target->getRadius());
		direction = target->getDir();
		up = target->getUp();
	}
	else if (state == CameraState::ThirdPerson) {
		//position = target->getPos() - (target->getDir() - target->getUp()*0.2).normalized()*target->getRadius() * 2;
		direction = target->getPos() - position;
		direction = direction.normalized();
		position = target->getPos() - direction*(target->getRadius()*scroll);
		if (fixCamera == true) {
			if (true || mouseLockTicks <= 0) {
				Vec3 desiredPos = target->getPos() - (target->getDir() - target->getUp()*0.2f).normalized()*target->getRadius() * scroll;
				Vec3 newPosition = position + (desiredPos - position)*fixingVelocity;
				direction = target->getPos() - newPosition;
				direction = direction.normalized();
				position = target->getPos() - direction*(target->getRadius() * scroll);
				if (target->getType() == OType::OPlayer) {
					Player *target = (Player *)this->target;
					position = position - direction*(target->getRadius()*target->getThrust()*thrustFactor);
				}
				up = up + (target->getUp() - up)*fixingVelocity;
			}
			else {
				mouseLockTicks--;
			}
		}
		//system("cls");
		//std::cout << position << " " << direction << std::endl;
	}
	
}

void Camera::apply() {
	gluLookAt(position.x, position.y, position.z,
		position.x + direction.x, position.y + direction.y, position.z + direction.z,
		up.x, up.y, up.z);
}

void Camera::handleMouseMove(int x, int y, float mouseSpeedX, float mouseSpeedY) {
	if ((x - glutGet(GLUT_WINDOW_WIDTH) / 2) == 0 && (y - glutGet(GLUT_WINDOW_HEIGHT) / 2) == 0)
		return;
	if (state == FirstPerson) {
		if (target->getType() == OCameraTarget) {
			Vec3 &dir = ((CameraTarget*)target)->direction;

			float dx = (x - glutGet(GLUT_WINDOW_WIDTH) / 2)*mouseSpeedX;
			float dy = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2)*mouseSpeedY;


			dir += dir.cross(up)*dx;//hotizontal move

			float len = up.distance(dir);
			bool invertDir = false;
			if (len > VEC3_SQRT2) {
				invertDir = true;
				Vec3 dif(up.x + dir.x, up.y + dir.y, up.z + dir.z);
				len = dif.length();
			}
			if (len > 0.08) { //avoid moving across the up and -up vector
				dir -= up*(dy / len);
			}
			else {
				if (invertDir) {
					if (dy < 0) {
						dir -= up*(dy / (len + VEC3_EPS)); //+0.0001 to avoid div by 0
					}
				}
				else {
					if (dy > 0) {
						dir -= up*(dy / (len + VEC3_EPS)); //+0.0001 to avoid div by 0
					}
				}
			}

			dir = dir.normalized();
		}
	}
	else if (state == ThirdPerson) {
		
		Vec3 dir = direction;
		float dx = (x - glutGet(GLUT_WINDOW_WIDTH) / 2)*mouseSpeedX;
		float dy = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2)*mouseSpeedY;

		if(dx > 0.01 || dy > 0.01)
			mouseLockTicks = refreshTicks;

		dir += dir.cross(up)*dx;//hotizontal move

		float len = up.distance(dir);
		bool invertDir = false;
		if (len > VEC3_SQRT2) {
			invertDir = true;
			Vec3 dif(up.x + dir.x, up.y + dir.y, up.z + dir.z);
			len = dif.length();
		}
		if (len > 0.08) { //avoid moving across the up and -up vector
			dir -= up*(dy / len);
		}
		else {
			if (invertDir) {
				if (dy < 0) {
					dir -= up*(dy / (len + VEC3_EPS)); //+0.0001 to avoid div by 0
				}
			}
			else {
				if (dy > 0) {
					dir -= up*(dy / (len + VEC3_EPS)); //+0.0001 to avoid div by 0
				}
			}
		}
		dir = dir.normalized();

		position = target->getPos() - (dir*(target->getRadius()*scroll));
	}
	else if (false) {
		mouseLockTicks = refreshTicks;
		float dx = (x - glutGet(GLUT_WINDOW_WIDTH) / 2)*mouseSpeedX;
		float dy = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2)*mouseSpeedY;

		Vec3 dir = direction;
		float r = sqrt(dir.z + dir.y + dir.x);
		float angle1 = acos(dir.y);
		float angle2 = atan2(dir.z, dir.x);
		angle1 += dy;
		angle2 += dx;
		dir.x = sin(angle1) * cos(angle2);
		dir.z = sin(angle1) * sin(angle2);
		dir.y = cos(angle1);

		dir = dir.normalized();
		position = target->getPos() - (dir*target->getRadius()*scroll);
	}
}

void Camera::setTarget(Object *_target) {
	target = _target;
}

void Camera::setState(CameraState _state) {
	if (_state == ThirdPerson) {
		position = target->getPos() - (target->getDir() - target->getUp()*0.2f).normalized()*target->getRadius() * scroll;
	}
	state = _state;
}

void Camera::changeFixCamera() {
	fixCamera = !fixCamera;
	mouseLockTicks = 0;
}

void Camera::changeScroll(bool state) {
	
	if (state == true) {
		if (scroll < maxScroll) {
			scroll += scrollVelocity;
		}
	}
	else {
		if (scroll > 1) {
			scroll -= scrollVelocity;
		}
	}
}

Object *Camera::getTarget() {
	return target;
}

CameraState Camera::getState() {
	return state;
}

Vec3 Camera::getPos() {
	return position;
}

Vec3 Camera::getDir() {
	return direction;
}

Vec3 Camera::getUp() {
	return up;
}