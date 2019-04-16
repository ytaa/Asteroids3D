#pragma once
#include "State.h"
#include "Input.h"
#include "InputMenu.h"
#include "StateManager.h"
#include "ResourceHolder.h"
#include "StateGame.h"
class StateMenu :
	public State
{
public:
	StateMenu(StateManager *, ResourceHolder *);
	~StateMenu();
	void update();
	void render();
	Input *getInput();
	float getZFar();
private:
	StateManager *stateManager;
	ResourceHolder *resources;
	InputMenu input;
	int frameCounter;
	float titleScale;
	bool titleScaleDir;
};

