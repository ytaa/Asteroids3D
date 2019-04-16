#include "InputGameOver.h"



InputGameOver::InputGameOver()
	:backToMenu(false)
	,fullScreen(false)
{
}


InputGameOver::~InputGameOver()
{
}


void InputGameOver::keyDown(unsigned char key, int xx, int yy) {
	if (key >= 65 && key <= 90) {
		key += 32;
	}
	if (key == 'f') {
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
	if (key == 13) {
		backToMenu = true;
	}
	if (key == 27)//Esc
		glutLeaveMainLoop();
}
void InputGameOver::specialKeyDown(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;

}
void InputGameOver::keyUp(unsigned char key, int xx, int yy) {
	if (key >= 65 && key <= 90) {
		key += 32;
	}
}
void InputGameOver::specialKeyUp(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;
}
void InputGameOver::mouseMove(int x, int y) {

}
void InputGameOver::mouseAction(int button, int state, int x, int y) {

}

bool InputGameOver::isBackToMenu() {
	return backToMenu;
}