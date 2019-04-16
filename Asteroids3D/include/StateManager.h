#pragma once
#include "State.h"
#include "ResourceHolder.h"

class StateManager
{
public:
	StateManager();
	~StateManager();
	State *getState();
	void newState(State *);

private:
	State *crState;
	ResourceHolder resources;
};

