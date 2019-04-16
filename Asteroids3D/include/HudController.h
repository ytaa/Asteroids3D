#pragma once
#include "Player.h"
#include "State.h"
#include <string>
class HudController
{
public:
	HudController(Player *);
	~HudController();

	void update();
	void render();

private:
	Player *player;
	std::string scoreTxt;
	std::string scoreValue;
	std::string inviolableTxt;
	bool isInviolable;
};

