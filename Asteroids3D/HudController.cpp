#include "HudController.h"
#include <iostream>


HudController::HudController(Player *_player)
	:player(_player)
	,scoreTxt(std::string("Score: "))
	,scoreValue(std::string("0"))
	,inviolableTxt(std::string("INVIOLABLE"))
	,isInviolable(false)
{
}


HudController::~HudController()
{
}

void HudController::update() {
	//score update
	scoreValue = std::to_string(player->getScore());
	
	//inviolability update
	isInviolable = player->isInviolable();
	//std::cout << GLUT_WINDOW_WIDTH << std::endl;
}

void HudController::render() {
	GLfloat wWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	GLfloat wHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	
	//Down side Bar
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex2f(0.0, 0.0);
	glVertex2f(wWidth, 0.0);
	glVertex2f(wWidth, wHeight*0.1f);
	glVertex2f(0.0, wHeight*0.1f);
	glEnd();
	glPopMatrix();

	//HP bar
	glPushMatrix();
	glTranslatef(70.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glColor3f(0.15f, 0.05f, 0.05f);
	glVertex2f(wWidth*0.7f - 5, wHeight*0.04f - 5);
	glVertex2f(wWidth*0.9f + 5, wHeight*0.04f - 5);
	glVertex2f(wWidth*0.9f + 5, wHeight*0.06f + 5);
	glVertex2f(wWidth*0.7f - 5, wHeight*0.06f + 5);

	glColor3f(0.35f, 0.05f, 0.05f);
	glVertex2f(wWidth*0.7f, wHeight*0.04f);
	glVertex2f(wWidth*0.7f + wWidth*0.2f*((float) player->getHP() / player->getMaxHP()), wHeight*0.04f);
	glVertex2f(wWidth*0.7f + wWidth*0.2f*((float) player->getHP() / player->getMaxHP()), wHeight*0.06f);
	glVertex2f(wWidth*0.7f, wHeight*0.06f);
	glEnd();
	glPopMatrix();

	//Score
	{
		float scaleWidth = 0.0002f *0.7f;
		float scaleHeight = 0.0003f *0.7f;
		std::string str = (scoreTxt + scoreValue);
		float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
		float textHeight = 104.76f * wHeight*scaleHeight;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(wWidth*0.04f, wHeight*0.05f - textHeight / 2, 0);
		glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
	
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
		glPopMatrix();
	}

	//Inviolability
	if (isInviolable) {
		float scaleWidth = 0.0002f;
		float scaleHeight = 0.0003f;
		float textWidth = 104.76f * inviolableTxt.length() * wWidth*scaleWidth;
		float textHeight = 104.76f * wHeight*scaleHeight;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH))/2 - textWidth/2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1, 0);
		glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)inviolableTxt.c_str());
		glPopMatrix();
	}

	if (player->getGameMode() == GMode::GTimeRush) {
		float scaleWidth = 0.0002f *0.7f;
		float scaleHeight = 0.0003f *0.7f;
		{
			std::string str = "Time left: ";
			int min = player->getTimeLeft() / 60;
			int sek = player->getTimeLeft() % 60;
			if (min < 10) {
				str += "0";
			}
			str += std::to_string(min) + ":";
			if (sek < 10) {
				str += "0";
			}
			str += std::to_string(sek);
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			if(player->getTimeLeft()<=10)
				glColor3f(0.75f, 0.15f, 0.15f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, wHeight*0.05f - textHeight / 2, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}

	}

	glPopMatrix();
	// Making sure we can render 3d again
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}