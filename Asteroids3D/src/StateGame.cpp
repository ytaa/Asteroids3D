#include "StateGame.h"
#include "StateManager.h"
#include "ParticleEmitter.h"
StateGame::StateGame(StateManager *_stateManager, ResourceHolder* _resources, GMode _gameMode)
	:stateManager(_stateManager)
	,resources(_resources)
	,cameraTarget(CameraTarget())
	,scene(Scene())
	,player(Player(&scene, _gameMode, &resources->starshipModel, &resources->starshipTexture))
	,camera(Camera(&player))
	,hud(HudController(&player))
	,meteors(std::vector<Meteor*>())
	,enemy(Enemy(&player, &meteors, &resources->spaceShipModel, &resources->spaceShipTexture))
	,input(InputGame(&cameraTarget, &player, &camera))
	,playerTarget(PlayerTarget(&player, &resources->playerTargetModel))
	,arenaSize(900.f)//700
	,skybox(SkyBox(player, &resources->spaceBoxModel, &resources->spaceBoxTexture, arenaSize/100.f))
	,lastUpdateTime(std::chrono::high_resolution_clock::now())
	,timeAccumulator(0.f)
	,frameCounter(0)
	,meteorsNumber(400)
	,gameMode(_gameMode)
{	
	
	scene.setCamera(&camera);
	scene.setHud(&hud);

	player.setLights(scene.getLight(1), scene.getLight(2));
	enemy.setLight(scene.getLight(3));

	scene.addObject(&cameraTarget);
	scene.addObject(&player);
	if (gameMode == GMode::GTimeRush) {
		scene.addObject(&playerTarget);
		player.setMaxHp(2);
	}
	else if (gameMode == GMode::GPursuit) {
		scene.addObject(&enemy);
		player.setMaxHp(3);
	}
	scene.addObject(&skybox);

	for (unsigned int i = 0; i < meteorsNumber; i++) {
		meteors.push_back(new Meteor(Vec3::random(-arenaSize/2,arenaSize/2), Vec3::random(-(Meteor::maxVelocity), Meteor::maxVelocity), rng::rand(Meteor::minRadius, Meteor::maxRadius), &resources->meteorModel, &resources->meteorTextures));
		scene.addObject(meteors[i]);
	}

}
StateGame::~StateGame(){
	for (unsigned int i = 0; i < meteors.size(); i++) {
		delete meteors[i];
	}
}
void StateGame::update(){

	auto currentTime = std::chrono::high_resolution_clock::now();
	float deltaTime = (currentTime - lastUpdateTime).count() / 1000000.f; //milliseconds
	lastUpdateTime = currentTime;
	timeAccumulator += deltaTime;

	while (timeAccumulator >= 17) {
		frameCounter++;
		input.apply();
		scene.update();
		if (player.getHP() <= 0 || (gameMode == GTimeRush && player.getTimeLeft() <= 0)) {
			stateManager->newState(new StateGameOver(stateManager, resources, player.getScore()));
			return;
		}
		if (gameMode == GMode::GTimeRush) {
			if (frameCounter % 60 == 0) {
				player.setScore(player.getScore() + 1);
				player.setTimeLeft(player.getTimeLeft() - 1);
			}
		}
		//respawn meteors that are too far away or destroyed
		Vec3 playerPos = player.getPos();
		float maxDist = sqrt((arenaSize/2)*(arenaSize/2) * 2)+Meteor::maxRadius + 10;
		for (unsigned int i = 0; i < meteorsNumber; i++) {
			if (playerPos.distance(meteors[i]->getPos()) > maxDist || meteors[i]->isDead()) {
				meteors[i]->respawn(playerPos, arenaSize-Meteor::maxRadius*2.f);
			}
		}
		glutFullScreen();
		timeAccumulator -= 17;
	}
}
void StateGame::render() {
	scene.render();
}

Scene *StateGame::getScene() {
	return &scene;
}
Input *StateGame::getInput() {
	return &input;
}

float StateGame::getZFar() {
	return arenaSize;
}
