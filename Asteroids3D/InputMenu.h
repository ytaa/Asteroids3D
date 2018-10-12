#pragma once
#include "Input.h"
#include "State.h"
#include <GL/freeglut.h>
class InputMenu :
	public Input
{
public:
	InputMenu();
	~InputMenu();
	void keyDown(unsigned char key, int xx, int yy);
	void specialKeyDown(int key, int xx, int yy);
	void keyUp(unsigned char key, int xx, int yy);
	void specialKeyUp(int key, int xx, int yy);
	void mouseMove(int x, int y);
	void mouseAction(int button, int state, int x, int y);
	bool isStartGame();
	GMode getSelectedMode();
private:
	bool startGame;
	bool fullScreen;
	GMode selectedMode;
};


