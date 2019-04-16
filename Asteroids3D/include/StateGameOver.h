#pragma once
#include "State.h"
#include "Input.h"
#include "InputGameOver.h"
#include "StateManager.h"
#include "ResourceHolder.h"
#include "StateMenu.h"
class StateGameOver :
	public State
{
public:
	StateGameOver(StateManager *, ResourceHolder *, unsigned int);
	~StateGameOver();
	void update();
	void render();
	Input *getInput();
	float getZFar();
private:
	StateManager *stateManager;
	ResourceHolder *resources;
	InputGameOver input;
	unsigned int score;
};

