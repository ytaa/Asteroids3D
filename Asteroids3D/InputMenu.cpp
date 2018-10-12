#include "InputMenu.h"



InputMenu::InputMenu()
	:startGame(false)
	, fullScreen(false)
	, selectedMode(GMode::GNone)
{
}


InputMenu::~InputMenu()
{
}


void InputMenu::keyDown(unsigned char key, int xx, int yy) {
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
	if (key == '1') {
		selectedMode = GMode::GTimeRush;
	}
	if (key == '2') {
		selectedMode = GMode::GPursuit;
	}
	if (key == '3') {
		glutLeaveMainLoop();
	}
	if (key == 'B' || key == 'b') {
		if (selectedMode != GMode::GNone)
			selectedMode = GMode::GNone;
	}
	if (key == 13) {
		if(selectedMode != GMode::GNone)
			startGame = true;
	}
	if (key == 27)//Esc
		glutLeaveMainLoop();
}
void InputMenu::specialKeyDown(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;

}
void InputMenu::keyUp(unsigned char key, int xx, int yy) {
	if (key >= 65 && key <= 90) {
		key += 32;
	}
}
void InputMenu::specialKeyUp(int key, int xx, int yy) {
	if (key >= 100)
		key -= 87;
}
void InputMenu::mouseMove(int x, int y) {

}
void InputMenu::mouseAction(int button, int state, int x, int y) {

}

bool InputMenu::isStartGame() {
	return startGame;
}

GMode InputMenu::getSelectedMode() {
	return selectedMode;
}