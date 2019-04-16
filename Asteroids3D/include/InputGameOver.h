#pragma once
#include "Input.h"
#include <GL/freeglut.h>
class InputGameOver :
	public Input
{
public:
	InputGameOver();
	~InputGameOver();
	void keyDown(unsigned char key, int xx, int yy);
	void specialKeyDown(int key, int xx, int yy);
	void keyUp(unsigned char key, int xx, int yy);
	void specialKeyUp(int key, int xx, int yy);
	void mouseMove(int x, int y);
	void mouseAction(int button, int state, int x, int y);
	bool isBackToMenu();
private:
	bool backToMenu;
	bool fullScreen;
};

