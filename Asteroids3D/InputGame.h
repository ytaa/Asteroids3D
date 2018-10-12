#pragma once
#include <GL/freeglut.h>
#include "Player.h"
#include "Camera.h"
#include "CameraTarget.h"
#include "Input.h"
class InputGame
	: public Input
{
public:
	InputGame(CameraTarget *, Player *, Camera *);
	~InputGame();
	void keyDown(unsigned char key, int xx, int yy);
	void specialKeyDown(int key, int xx, int yy);
	void keyUp(unsigned char key, int xx, int yy);
	void specialKeyUp(int key, int xx, int yy);
	void mouseMove(int x, int y);
	void mouseAction(int button, int state, int x, int y);
	void apply();
	//SETTINGS
	bool mouseCapture = true;
	float mouseSpeedX = 0.001f;
	float mouseSpeedY = 0.001f;
	float moveSpeed = 3.4f;
private:
	CameraTarget *cameraTarget;
	Player *starship;
	Camera *camera;
	bool keyState[INPUT_KEYSNUMBER];
	bool fullScreen;
};

