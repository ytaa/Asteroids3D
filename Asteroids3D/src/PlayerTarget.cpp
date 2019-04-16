#include "PlayerTarget.h"
#include "Player.h"
#include "Model3D.h"


PlayerTarget::PlayerTarget(Player *_player, Model3D *_model)
	:spawningAreaMax(300.f)
	,spawningAreaMin(200.f)
	,player(_player)
	,playerDirectionMarker(DirectionMarker(player, this))
	,position(Vec3(100.f,100.f,100.f))
	,direction(Vec3(0,0,1.f))
	,radius(4.f)
	,score(10)
	,minScore(5)
	,maxScore((unsigned int)spawningAreaMax/10)
	,frameCounter(0)
	,model(_model)
	,type(OType::OPlayerTarget)
{
	respawn();
}


PlayerTarget::~PlayerTarget()
{
}

int PlayerTarget::update() {
	frameCounter++;
	playerDirectionMarker.update();
	/*if (frameCounter % 30 == 0)
		if (score > minScore)
			score -= 2;
		else if (score < minScore)
			score = minScore;*/
	return 0;
}
void PlayerTarget::render() {
	
	Vec3 playerPos = player->getPos();
	//Rendering target pointer
	glPushMatrix();



	glEnable(GL_COLOR_MATERIAL);
	Vec3 z = position - playerPos;
	Vec3 x = Vec3(0, 1, 0).cross(z);
	Vec3 y = z.cross(x);

	x = x.normalized();
	y = y.normalized();
	z = z.normalized();

	float markerRotationMatrix[16];
	markerRotationMatrix[0] = x.x;
	markerRotationMatrix[1] = x.y;
	markerRotationMatrix[2] = x.z;
	markerRotationMatrix[3] = 0;

	markerRotationMatrix[4] = y.x;
	markerRotationMatrix[5] = y.y;
	markerRotationMatrix[6] = y.z;
	markerRotationMatrix[7] = 0;

	markerRotationMatrix[8] = z.x;
	markerRotationMatrix[9] = z.y;
	markerRotationMatrix[10] = z.z;
	markerRotationMatrix[11] = 0;

	markerRotationMatrix[12] = 0;
	markerRotationMatrix[13] = 0;
	markerRotationMatrix[14] = 0;
	markerRotationMatrix[15] = 1;

	z = z*radius;

	//marker
	playerDirectionMarker.render();

	//and target
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.1f, 0.35f, 0.1f);
	
	//glColor3f(0.0f, 1.f, 0.0f);
	glTranslatef(position.x, position.y, position.z);
	if(model){
		glMultMatrixf(markerRotationMatrix);
		glRotatef(90.f, 1, 0, 0);
		glScalef(radius / 100.f, radius / 100.f, radius / 100.f);
		model->call();
	}
	else {
		glRotatef(13.f, 1, 0, 0);
		glRotatef(13.f, 0, 1, 0);
		glRotatef(13.f, 0, 0, 1);
		glutSolidCube(radius);
	}
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();



	glPopMatrix();

}
Vec3 PlayerTarget::getPos() {
	return position;
}
Vec3 PlayerTarget::getDir() {
	return direction;
}
Vec3 PlayerTarget::getUp() {
	return Vec3(0, 1, 0);
}
float PlayerTarget::getRadius() {
	return radius;
}
unsigned int PlayerTarget::getScore() {
	return score;
}
OType PlayerTarget::getType() {
	return type;
}

void PlayerTarget::respawn() {
	position = Vec3::random(-spawningAreaMax, spawningAreaMax);
	score = (unsigned int)position.distance(player->getPos())/30;
	if (score < minScore) {
		score = minScore;
	}
	else if (score > maxScore) {
		score = maxScore;
	}
	player->setTimeLeft(player->getTimeLeft() + 7);
	//std::cout << score << std::endl;
	/*
	float r = rng::randFloat(0, 8);
	Vec3 playerPos = player->getPos();
	if (r < 1) {
		position = Vec3(playerPos.x + rng::randFloat(spawningAreaMin, spawningAreaMax), 
						playerPos.y + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z + rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 2) {
		position = Vec3(playerPos.x + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z - rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 3) {
		position = Vec3(playerPos.x + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z + rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 4) {
		position = Vec3(playerPos.x + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z - rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 5) {
		position = Vec3(playerPos.x - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z + rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 6) {
		position = Vec3(playerPos.x - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y + rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z - rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else if (r < 7) {
		position = Vec3(playerPos.x - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z + rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	else {
		position = Vec3(playerPos.x - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.y - rng::randFloat(spawningAreaMin, spawningAreaMax),
						playerPos.z - rng::randFloat(spawningAreaMin, spawningAreaMax));
	}
	*/
}