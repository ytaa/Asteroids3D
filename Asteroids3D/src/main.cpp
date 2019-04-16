#include <GL/freeglut.h>
#include <windows.h> 
#include <cmath>
#include <vector>
#include <iostream>
#include "Vec3.h"
#include "StateManager.h"

StateManager* stateManager;

void update() {
	stateManager->getState()->update();
}

void render() {
	stateManager->getState()->render();
}

void keyDown(unsigned char key, int xx, int yy) {
	stateManager->getState()->getInput()->keyDown(key, xx, yy);
}

void specialKeyDown(int key, int xx, int yy) {
	stateManager->getState()->getInput()->specialKeyDown(key, xx, yy);
}
void keyUp(unsigned char key, int xx, int yy) {
	stateManager->getState()->getInput()->keyUp(key, xx, yy);
}
void specialKeyUp(int key, int xx, int yy) {
	stateManager->getState()->getInput()->specialKeyUp(key, xx, yy);
}
void mouseMove(int x, int y) {
	stateManager->getState()->getInput()->mouseMove(x,y);
}
void mouseAction(int button, int state, int x, int y) {
	stateManager->getState()->getInput()->mouseAction(button, state, x, y);
}

void mouseEntry(int state) {
	return;
}


void reshape(GLsizei width, GLsizei height) { 
	if (height == 0) 
		height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, stateManager->getState()->getZFar());
}

void timer(int id) {
	glutTimerFunc(17,timer,0);
	stateManager->getState()->update();
	return;
}

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	glEnable(GL_NORMALIZE); // Enabling the mode forces OpenGL to normalize transformed normals to be of unit length. Necessary because of loaded model scaling

	glEnable(GL_CULL_FACE); // W³¹czenie face culling'u, czyli nie renderowanie dwóch stron prymitywów
	glFrontFace(GL_CCW); // Interpretacja jako przednich œcian tych, które s¹ rysowane w kierunku przeciwnym do ruchu zegara. Alternatywa : GL_CW
	glCullFace(GL_BACK); // Ustawienie cullingu na tylne œciany, wiêc tylko przednie bêd¹ renderowane

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
		//lights
	glEnable(GL_LIGHTING);	//Enable lighting calculation
	float globAmb[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); //disable default global ambient
	//glEnable(GL_COLOR_MATERIAL); //enable color for materials

	//glClearColor(0.2f, 0.f, 0.2f, 1);

}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(800, 600);   // Set the window's initial width & height
	//glutInitWindowSize(1024, 768);
	glutInitWindowPosition(700, 150); // Position the window's initial top-left corner, -1 => letting windows menager to decide

	//glutInitWindowPosition(0, 0);
	//glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	
	glutCreateWindow("Asteroids3D");          // Create window with the given title
	glutFullScreen();
	
	glutDisplayFunc(render);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutIdleFunc(render);
	glutKeyboardFunc(keyDown);
	glutSpecialFunc(specialKeyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialUpFunc(specialKeyUp);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);
	glutEntryFunc(mouseEntry);
	glutMouseWheelFunc(mouseAction);
	glutTimerFunc(17, timer, 0);

	glutIgnoreKeyRepeat(1);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	initGL();						// Our own OpenGL initialization
	stateManager = new StateManager();
	
	glutMainLoop();      // Enter the infinite event-processing loop
	delete stateManager;
	
	return 0;
}