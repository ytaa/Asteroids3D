#pragma once
#include "Input.h"
enum GMode {
	GTimeRush,
	GPursuit,
	GNone
};
class State
{
public:
	State();
	virtual ~State();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual Input *getInput() = 0;
	virtual float getZFar() = 0;
};

