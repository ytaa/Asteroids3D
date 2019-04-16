#include "StateManager.h"
#include "StateMenu.h"


StateManager::StateManager()
	:resources(ResourceHolder())
	,crState(new StateMenu(this, &resources))
{
}


StateManager::~StateManager()
{
	delete crState;
}

State *StateManager::getState() {
	return crState;
}

void StateManager::newState(State *_state) {
	delete crState;
	crState = _state;
}
