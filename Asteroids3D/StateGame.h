#pragma once
#include <chrono>
#include "State.h"
#include "StateGameOver.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "Player.h"
#include "Meteor.h"
#include "InputGame.h"
#include "ResourceHolder.h"
#include "CameraTarget.h"
#include "SkyBox.h"
#include "PlayerTarget.h"
#include "HudController.h"
#include "Enemy.h"
#include "rng.h"

class StateManager;
class StateGame
	: public State
{
public:
	StateGame(StateManager *, ResourceHolder *, GMode);
	~StateGame();
	void update();
	void render();
	Scene* getScene();
	Input* getInput();
	float getZFar();


private:
	StateManager *stateManager;
	ResourceHolder *resources;
	CameraTarget cameraTarget;
	Scene scene;
	Player player;
	Camera camera;
	HudController hud;
	std::vector<Meteor*> meteors;
	Enemy enemy;
	InputGame input;
	PlayerTarget playerTarget;
	float arenaSize;
	SkyBox skybox;
	//std::vector<Enemy> enemies;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;
	float timeAccumulator;
	unsigned int frameCounter;
	unsigned int meteorsNumber;
	GMode gameMode;
};