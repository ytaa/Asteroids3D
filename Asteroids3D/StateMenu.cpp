#include "StateMenu.h"
#include <string>

StateMenu::StateMenu(StateManager *_stateManager, ResourceHolder *_resources)
	:stateManager(_stateManager)
	, resources(_resources)
	, input(InputMenu())
	, frameCounter(1)
	, titleScale(1.f)
	, titleScaleDir(true)
{
	//glutFullScreen();
}


StateMenu::~StateMenu()
{
}

void StateMenu::update() {
	frameCounter++;
	if (frameCounter % 5)
		frameCounter = 1;

	if (titleScaleDir == true) {
		if (titleScale >= 1.2f) {
			titleScaleDir = false;
		}
		else {
			titleScale += 0.0075f;
		}
	}
	else {
		if (titleScale <= 1.f) {
			titleScaleDir = true;
		}
		else {
			titleScale -= 0.0075f;
		}
	}

	if (input.isStartGame()) {
		glutReshapeWindow(800, 600);
		//glutFullScreen();
		stateManager->newState(new StateGame(stateManager, resources, input.getSelectedMode()));
		return;
	}
}
void StateMenu::render() {
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

	if (input.getSelectedMode() == GMode::GNone) {
		{
			float scaleWidth = 0.0005f * titleScale;
			float scaleHeight = 0.00075f * titleScale;
			float textWidth = 104.76f * strlen("ASTEROIDS 3D") *wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.075f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)"ASTEROIDS 3D");
			glPopMatrix();
		}

		{
			std::string str = "Select game mode:";
			float scaleWidth = 0.0002f;
			float scaleHeight = 0.0003f;
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.05f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}



		{
			std::string str = "1. Time rush";
			float scaleWidth = 0.0002f;
			float scaleHeight = 0.0003f;
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.15f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}

		{
			std::string str = "2. Pursuit";
			float scaleWidth = 0.0002f;
			float scaleHeight = 0.0003f;
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.25f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "3. Exit";
			float scaleWidth = 0.0002f;
			float scaleHeight = 0.0003f;
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.35f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
	}
	else {
		if (input.getSelectedMode() == GMode::GTimeRush) {
			{
				std::string str = "Mission: Time Rush";
				float scaleWidth = 0.0004f;
				float scaleHeight = 0.0006f;
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.25f, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			float scaleWidth = 0.0002f *0.7f;
			float scaleHeight = 0.0003f *0.7f;
			{
				std::string str = "Your mission is to reach as many green checkpoints as possible."; //\n Checkpoints will appear one by one.\n You will have to get to each checkpoint in a\n given time.If the time passes you won't get any points.";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = "Checkpoints will appear one by one and they'll be marked by a"; 
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight*2, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = "pointer. Each checkpoint will give you some extra time.";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight * 2 * 2, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = "If the time passes you will lose";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight * 2 * 3, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}

		}
		else if (input.getSelectedMode() == GMode::GPursuit) {
			{
				std::string str = "Mission: Pursuit";
				float scaleWidth = 0.0004f;
				float scaleHeight = 0.0006f;
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.25f, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			float scaleWidth = 0.0002f *0.7f;
			float scaleHeight = 0.0003f *0.7f;
			{
				std::string str = "Your mission is to destroy as many enemies as possible."; //\n Checkpoints will appear one by one.\n You will have to get to each checkpoint in a\n given time.If the time passes you won't get any points.";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = "Enemies will appear one by one and they'll be marked";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight * 2, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = " by a pointer. The score you get from a enemy is based on ";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight * 2 * 2, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}
			{
				std::string str = "how fast you destroy it.";
				float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
				float textHeight = 104.76f * wHeight*scaleHeight;
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 + wHeight*0.1f - textHeight * 2 * 3, 0);
				glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
				glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
				glPopMatrix();
			}

		}
		{
			std::string str = "Controls";
			float scaleWidth = 0.0002f * 1.2f;
			float scaleHeight = 0.0003f * 1.2f;
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.15f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
			float scaleWidth = 0.0002f*0.7f;
			float scaleHeight = 0.0003f*0.7f;
		{
			std::string str = "W / S - Thrust / Drag";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "Left / Right (A / D) -  Roll";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "Up / Down - Pitch";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2 * 2, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "Q / E - Yaw";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2 * 3, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "Space - Fire missiles";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) / 2 - textWidth / 2, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2 * 4, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "Enter to continue ->";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(((float)glutGet(GLUT_WINDOW_WIDTH)) - textWidth - wWidth*0.01, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2 * 5, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}
		{
			std::string str = "<- Press B to Back";
			float textWidth = 104.76f * str.length() * wWidth*scaleWidth;
			float textHeight = 104.76f * wHeight*scaleHeight;
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(wWidth*0.01, ((float)glutGet(GLUT_WINDOW_HEIGHT)) / 2 + textHeight / 2 - wHeight*0.22f - textHeight * 2 * 5, 0);
			glScalef(wWidth*scaleWidth, wHeight*scaleHeight, 1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)str.c_str());
			glPopMatrix();
		}

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
Input *StateMenu::getInput() {
	return &input;
}
float StateMenu::getZFar() {
	return 1.f;
}
