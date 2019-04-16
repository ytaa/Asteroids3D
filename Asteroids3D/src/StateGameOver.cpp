#include "StateGameOver.h"
#include <string>

StateGameOver::StateGameOver(StateManager *_stateManager, ResourceHolder *_resources, unsigned int _score)
	:stateManager(_stateManager)
	,resources(_resources)
	,input(InputGameOver())
	,score(_score)
{
}


StateGameOver::~StateGameOver()
{
}

void StateGameOver::update() {
	if (input.isBackToMenu()) {
		stateManager->newState(new StateMenu(stateManager, resources));
		return;
	}
}
void StateGameOver::render() {
	Sleep(1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Score

	GLfloat wWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	GLfloat wHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

	{
		float scaleWidth = 0.0004f;
		float scaleHeight = 0.0006f;
		float textWidth = 104.76f * strlen("GAME OVER") *wWidth*scaleWidth;
		float textHeight = 104.76f * wHeight*scaleHeight;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2, 0);
		glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)"GAME OVER");
		glPopMatrix();
	}

	{
		std::string str = "Your score was: " + std::to_string(score);
		float scaleWidth = 0.0002f;
		float scaleHeight = 0.0003f;
		float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
		float textHeight = 104.76f * wHeight*scaleHeight;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.1f, 0);
		glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
		glPopMatrix();
	}
	


	{
		float scaleWidth = 0.00015f;
		float scaleHeight = 0.000225f;
		float textWidth = 104.76f * strlen("Press Enter to go back to menu") *wWidth*scaleWidth;
		float textHeight = 104.76f * wHeight*scaleHeight;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.3f, 0);
		glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)"Press Enter to go back to menu");
		glPopMatrix();
	}
	
	// Making sure we can render 3d again
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
Input *StateGameOver::getInput() {
	return &input;
}
float StateGameOver::getZFar() {
	return 1.f;
}