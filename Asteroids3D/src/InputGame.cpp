#include "InputGame.h"

InputGame::InputGame(CameraTarget *_cameraTarget, Player *_starship, Camera *_camera)
	:cameraTarget(_cameraTarget)
	,starship(_starship)
	,camera(_camera)
	,fullScreen(true)
{
	for (int i = 0; i < INPUT_KEYSNUMBER; i++)
		keyState[i] = false;
}


InputGame::~InputGame()
{
}

void InputGame::apply() {
	//std::cout <<cameraTarget.position << " " << keyState['w'] << std::endl;
	if (mouseCapture) {
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	if (camera->getState() == CameraState::FirstPerson) {

		Vec3 &pos = cameraTarget->position;
		Vec3 &dir = cameraTarget->direction;
		Vec3 &up = cameraTarget->up;

		if (keyState['w']) {
			pos += dir*moveSpeed;
		}
		if (keyState['s']) {
			pos -= dir*moveSpeed;
		}
		if (keyState['d']) {
			pos += dir.cross(up).normalized()*moveSpeed;
		}
		if (keyState['a']) {
			pos -= dir.cross(up).normalized()*moveSpeed;
		}
		if (keyState['q']) {
			up += up.cross(dir).normalized()*0.1f;
		}
		if (keyState['e']) {
			up -= up.cross(dir).normalized()*0.11f;
		}
		if (keyState[' ']) {
			pos += up*moveSpeed;
		}
		if (keyState[INPUT_KEY_LSHIFT]) {
			pos -= up*moveSpeed;
		}
	} 
	else if (camera->getState() == CameraState::ThirdPerson) {
		if (keyState[INPUT_KEY_UP]) {
			starship->changePitch(true);
		}
		if (keyState[INPUT_KEY_DOWN]) {
			starship->changePitch(false);
		}
		if (keyState[INPUT_KEY_RIGHT] || keyState['d']) {
			starship->changeRoll(true);
		}
		if (keyState[INPUT_KEY_LEFT] || keyState['a']) {
			starship->changeRoll(false);
		}
		if (keyState['q']) {
			starship->changeYaw(true);
		}
		if (keyState['e']) {
			starship->changeYaw(false);
		}
		if (keyState['w']) {
			//starship.position += starship.direction*moveSpeed;
			starship->changeThrust();
		}
		if (keyState['s']) {
			//starship.position -= starship.direction*moveSpeed;
			starship->changeDrag();
		}
		if (keyState[' ']) {
			starship->fireMissile();
		}
		if (keyState['n']) {
			keyState['n'] = false;
			camera->changeFixCamera();
		}
	}
	if (keyState[INPUT_KEY_F1]) {
		if (camera->getState() != FirstPerson) {
			cameraTarget->position = camera->getPos();
			cameraTarget->direction = camera->getDir();
			cameraTarget->up = camera->getUp();
			camera->setTarget(cameraTarget);
			camera->setState(FirstPerson);
		}
	}
	if (keyState[INPUT_KEY_F2]) {
		if (camera->getState() != ThirdPerson) {
			camera->setTarget(starship);
			camera->setState(ThirdPerson);
		}
	}
	if (keyState['m']) {
		keyState['m'] = false;
		if (mouseCapture) {
			mouseCapture = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			mouseCapture = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
	if (keyState['f']) {
		keyState['f'] = false;
		if (fullScreen) {
			glutPositionWindow(700, 150);
			glutReshapeWindow(800, 600);
			fullScreen = false;
		}
		else {
			glutFullScreen();
			fullScreen = true;
		}
	}
	if (keyState[27])//Esc
		glutLeaveMainLoop();
	
}

void InputGame::keyDown(unsigned char key, int xx, int yy) {
	if (key >= 65 && key <= 90) {
		key += 32;
	}
	keyState[key] = true;
	//std::cout << key <<std::endl;
}
void InputGame::specialKeyDown(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;
	keyState[key + INPUT_FIRST_SPECIAL_KEY] = true;

}
void InputGame::keyUp(unsigned char key, int xx, int yy) {
	if (key >= 65 && key <= 90) {
		key += 32;
	}
	keyState[key] = false;
}
void InputGame::specialKeyUp(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;
	keyState[key + INPUT_FIRST_SPECIAL_KEY] = false;
}
void InputGame::mouseMove(int x, int y) {
	//todo sprawdzenie czy okno jest aktywne
	if (!mouseCapture)
		return;


	camera->handleMouseMove(x, y, mouseSpeedX, mouseSpeedY);
	
	return;
}
void InputGame::mouseAction(int button, int state, int x, int y) {
	if (camera->getState() == CameraState::ThirdPerson) {
		if (button == 0 || button == 3 || button == 4) {
			if (state == GLUT_UP) {
				camera->changeScroll(false);
			}
			else {
				camera->changeScroll(true);
			}
		}
	}
}