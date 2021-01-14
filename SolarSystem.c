/********************************************************************

	File: SolarSystem.c

	Description: A planetary system with a sun, orbiting planets, 
				 moons, and spaceships.

	Author: Victoria Byrka

*********************************************************************/

#include <freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// PI
#define PI 3.14159265359

// keyboard options
GLint showRings = 0;
GLint sparkleStars = 0;
GLint corona = 0;
GLint showSpaceship = 0; 

// special key options
GLint upKey = 0;
GLint downKey = 0;

// movement variables
GLfloat xPos = 0.0, yPos = 0.0;

// window size
GLint windowHeight = 500;
GLint windowWidth = 800;

// for all the spheres drawn
GLUquadric* quad, * q2, * q3, * q4, * q5, * q6, * q7, * q8, * q9, * q10, * q11, * q12;

// parameters for planets (gluSphere)
GLdouble radius;
GLint slices = 50;
GLint stacks = 10;

// current camera position
GLfloat cameraPosition[] = { 0, 0, 5 };

// interp value
GLfloat interp = 0.0;
GLfloat interpDif = 0.0005;

// camera movement values
GLfloat zoomOut = 20;
GLfloat zoomIn = 20;

// random float from 0.0 to 1.0 for colours
GLfloat randomFloat() {
	return (GLfloat)rand() / RAND_MAX;
}

// random float from -1.0 to 1.0 for position
GLfloat randomFloatPos() {
	return (GLfloat)rand() / RAND_MAX * 2 - 1;
}

// variables for orbiting planets and moons
GLdouble rotationAngle, rotationAngle2, rotationAngle3, rotationAngle4, rotationAngle5, rotationAngle6;
GLfloat rotation;

/********************************************************************

	Function: drawSun

	Description: Draws a sphere for the sun.

*********************************************************************/
void drawSun() {
	quad = gluNewQuadric();
	radius = 0.05;
	slices = 50;
	stacks = 10;
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	gluSphere(quad, radius, slices, stacks);
}

/********************************************************************

	Function: drawOrbits

	Description: Draws orbits for the planets.

*********************************************************************/
void drawOrbits(GLfloat orbRadius) {
	// white
	glColor3f(1.0, 1.0, 1.0);

	// set line width to 1
	glLineWidth(1.0);

	// line loop looks smoother than line
	glBegin(GL_LINE_LOOP);
	int i;
	for (i = 0; i < 360; i++)
	{
		double angle = 2 * 3.14159 * i / 360;
		double x = orbRadius * cos(angle);
		double y = orbRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

/********************************************************************

	Functions: drawPlanet1, drawPlanet2, drawPlanet3, drawPlanet4
			   drawPlanet5, drawPlanet6

	Description: Draws spheres for the planets.

*********************************************************************/
void drawPlanet1() {
	q2 = gluNewQuadric();
	radius = 0.06;
	glColor3f(0.5, 0.0, 0.0); // maroon
	glTranslatef(0.25, 0.0, 0.0);
	gluSphere(q2, radius, slices, stacks);
}

void drawPlanet2() {
	q3 = gluNewQuadric();
	radius = 0.03;
	glColor3f(0.53, 0.81, 0.92); // sky blue
	glTranslatef(0.4, 0.0, 0.0);
	gluSphere(q3, radius, slices, stacks);
}

void drawPlanet3() {
	q4 = gluNewQuadric();
	radius = 0.05;
	glColor3f(0.68, 1.0, 0.18); // green-yellow
	glTranslatef(0.55, 0.0, 0.0);
	gluSphere(q4, radius, slices, stacks);
}

void drawPlanet4() {
	q5 = gluNewQuadric();
	radius = 0.04;
	glColor3f(0.5, 1.0, 0.83); // aquamarine
	glTranslatef(0.7, 0.0, 0.0);
	gluSphere(q5, radius, slices, stacks);
}

void drawPlanet5() {
	q6 = gluNewQuadric();
	radius = 0.05;
	glColor3f(0.54, 0.17, 0.89); // violet
	glTranslatef(0.8, 0.0, 0.0);
	gluSphere(q6, radius, slices, stacks);
}

void drawPlanet6() {
	q7 = gluNewQuadric();
	radius = 0.08;
	glColor3f(1.0, 0.4, 0.7); // pink
	glTranslatef(0.95, 0.0, 0.0);
	gluSphere(q7, radius, slices, stacks);
}

/********************************************************************

	Function: drawMoons1, drawMoons2, drawMoons3

	Description: Draws spheres for the moons.

*********************************************************************/
void drawMoons1() {
	q8 = gluNewQuadric();
	radius = 0.01;
	glColor3f(1.0, 0.7, 0.8); // pink
	glTranslatef(0.1, 0.0, 0.0);
	gluSphere(q8, radius, slices, stacks);

	q9 = gluNewQuadric();
	radius = 0.018;
	glColor3f(1.0, 0.0, 1.0); // magenta
	glTranslatef(-0.2, 0.0, 0.0);
	gluSphere(q9, radius, slices, stacks);

}

void drawMoons2() {
	q10 = gluNewQuadric();
	radius = 0.015;
	glColor3f(0.5, 0.0, 0.5); // purple
	glTranslatef(0.1, 0.0, 0.0);
	gluSphere(q10, radius, slices, stacks);
}

void drawMoons3(){
	q11 = gluNewQuadric();
	radius = 0.012;
	glColor3f(1.0, 0.55, 0.0); // dark orange
	glTranslatef(0.08, 0.0, 0.0);
	gluSphere(q11, radius, slices, stacks);
}

/********************************************************************

	Function: drawStars

	Description: Draws random stars in background.

*********************************************************************/
void drawStars() {
	int i;
	glBegin(GL_POINTS);
	for (i = 0; i < 10; i++) {
		glColor3f(randomFloat(), randomFloat(), randomFloat());
		glVertex3f(randomFloatPos(), randomFloatPos(), randomFloatPos());
	}
	glEnd();
}

/********************************************************************

	Function: drawCorona

	Description: Draws a fiery corona for the sun.

*********************************************************************/
void drawCorona() {
	// turn on transparency blending
	glEnable(GL_BLEND);
	// set the blending mode to be controlled by ALPHA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set line width to 8
	glLineWidth(8.0);
	
	int i;
	glBegin(GL_LINES);
	for (i = 0; i < 360; i++) {

		double angle = 2 * 3.14159 * i/360;
		double x = 0.1 * cos(angle);
		double y = (GLfloat)rand() / RAND_MAX * 0.2 - 0.1;
		double z = 0.1 * sin(angle);

		// non-transparent yellow
		glColor4f(1.0, 1.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);

		// transparent yellow
		glColor4f(1.0, 1.0, 0.0, 0.0);
		glVertex3f(x, y, z);
	}
	glEnd();
}

/********************************************************************

	Function: drawSpaceship

	Description: Draws a spaceship.

*********************************************************************/
void drawSpaceship() {

	// draw a triangle
	glBegin(GL_TRIANGLES);
		// set the drawing to be blue
		glColor3f(0.4, 0.4, 0.9);
		glVertex2f(-1.0, 0.8);
		// set the drawing to be purple
		glColor3f(1.0, 0, 1.0);
		glVertex2f(-1.0, 1.0);
		// set the drawing to be dark grey
		glColor3f(0.1, 0.2, 0.2);
		glVertex2f(-0.8, 0.8);
	glEnd();

	glColor3f(0.8, 0.8, 0.8); // grey
	glTranslatef(-1.0, 0.9, 0.0);
	q12 = gluNewQuadric();
	radius = 0.03;
	gluSphere(q12, radius, slices, stacks);
}

/********************************************************************

	Function: myDisplay

	Description: Display to screen.

*********************************************************************/
void myDisplay() {

	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix into the model view matrix
	glLoadIdentity();

	// set the camera position
	gluLookAt(0, -4.5, 1,
		0, 0, 0,
		0, 1, 0);

	// if 's' is pressed then draw stars in background
	if (sparkleStars) {
		drawStars();
	}

	// clear the depth buffer to keep stars in the background
	glClear(GL_DEPTH_BUFFER_BIT);	

	// move with camera
	glTranslatef(0, -yPos, 0);

	// if 'f' is pressed show fleet of spaceships
	if (showSpaceship) {
		glPushMatrix();
		drawSpaceship();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.1, -0.2, 0.0);
		drawSpaceship();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.4, 0.4, 0.0);
		drawSpaceship();
		glPopMatrix();
	}

	// if 'r' is pressed
	if (showRings) {
		// draw orbits
		drawOrbits(0.25);
		drawOrbits(0.4);
		drawOrbits(0.55);
		drawOrbits(0.68);
		drawOrbits(0.8);
		drawOrbits(0.95);
	}
	
	// draw the sun
	drawSun();

	// if 'c' is pressed then draw sun's corona
	if (corona) {
		drawCorona();
	}

	// draw all planets with individual orbits, speeds, and some with moons

	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle, 0.0, 0.0, 0.1);
	drawPlanet1();
	drawMoons3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle2, 0.0, 0.0, 0.1);
	drawPlanet2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle3, 0.0, 0.0, 0.1);
	drawPlanet3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle4, 0.0, 0.0, 0.1);
	drawPlanet4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle5, 0.0, 0.0, 0.1);
	drawPlanet5();
	drawMoons2();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.00001 * cos(rotation / 0.25), 0.0, 0.00001 * sin(rotation / 0.25));
	glRotatef(rotationAngle6, 0.0, 0.0, 0.1);
	drawPlanet6();
	drawMoons1();
	glPopMatrix();

	// swap the drawing buffers
	glutSwapBuffers();
}

/********************************************************************

	Function: myControls

	Description: Prints possible keyboard controls.

*********************************************************************/
void myControls() {
	printf("Scene Controls\n");
	printf("-------------------------\n");
	printf("r:  toggle rings\n");
	printf("s:  toggle stars\n");
	printf("c:  toggle the sun's corona\n");
	printf("f:  toggle spaceship fleet\n");
	printf("q:  quit\n");
	printf("\n");
	printf("Camera Controls\n");
	printf("-------------------------\n");
	printf("Up    Arrow:  move up\n");
	printf("Down  Arrow:  move down\n");
	printf("PAGE  UP:     forward\n");
	printf("PAGE  DOWN:   backward\n");
}

/********************************************************************

	Function: myKeyboard

	Description: Determines which key is pressed.

*********************************************************************/
void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case'r':
		showRings = !showRings;
		glutPostRedisplay();
		break;
	case's':
		sparkleStars = !sparkleStars;
		glutPostRedisplay();
		break;
	case'c':
		corona = !corona;
		glutPostRedisplay();
		break;
	case'f':
		showSpaceship = !showSpaceship;
		glutPostRedisplay();
		break;
	case'q':
		exit(0);
	}
}

/********************************************************************

	Function: specialKeys

	Description: Determines which special key is pressed.

*********************************************************************/
void specialKeys(unsigned char key, int x, int y) {

	// flag while up arrow is pressed
	if (key == GLUT_KEY_UP) {
		upKey = 1;
	}

	// flag while down arrow is pressed
	if (key == GLUT_KEY_DOWN) {
		downKey = 1;
	}

	switch (key) {
	case GLUT_KEY_PAGE_UP:
		zoomIn = zoomOut -=1;
		zoomIn -= 1;
	
		// change into projection mode so that we can change the camera properties
		glMatrixMode(GL_PROJECTION);

		// load the identity matrix into the projection matrix
		glLoadIdentity();

		// gluPerspective(fovy, aspect, near, far)
		gluPerspective(zoomIn, (float)windowWidth / (float)windowHeight, 0.1, 100);

		// change into model-view mode so that we can change the object positions
		glMatrixMode(GL_MODELVIEW);
		break;

	case GLUT_KEY_PAGE_DOWN:
		zoomOut = zoomIn += 1;
		zoomOut += 1;
		// change into projection mode so that we can change the camera properties
		glMatrixMode(GL_PROJECTION);

		// load the identity matrix into the projection matrix
		glLoadIdentity();

		// gluPerspective(fovy, aspect, near, far)
		gluPerspective(zoomOut, (float)windowWidth / (float)windowHeight, 0.1, 100);

		// change into model-view mode so that we can change the object positions
		glMatrixMode(GL_MODELVIEW);
		break;
	}
	glutPostRedisplay();
}

/********************************************************************

	Function: mySpecialKeyboardReleased

	Description: Determines which special key is released.

*********************************************************************/
void mySpecialKeyboardReleased(unsigned char key, int x, int y) {

	// check if up arrow is released
	if (key == GLUT_KEY_UP) {
		upKey = 0;
	}

	// check if down arrow is released
	if (key == GLUT_KEY_DOWN) {
		downKey = 0;
	}
}

/************************************************************************

	Function:		myIdle

	Description:	Updates the animation when idle.

*************************************************************************/
void myIdle()
{
	// update rotation
	rotation += 0.1;

	// update various rotations of planets

	rotationAngle += 0.1;
	if (rotationAngle > 360) {
		rotationAngle = -360;
	}
	rotationAngle2 += 0.02;
	if (rotationAngle2 > 360) {
		rotationAngle2 = -360;
	}
	rotationAngle3 += 0.05;
	if (rotationAngle3 > 360) {
		rotationAngle3 = -360;
	}
	rotationAngle4 += 0.3;
	if (rotationAngle4 > 360) {
		rotationAngle4 = -360;
	}
	rotationAngle5 += 0.01;
	if (rotationAngle5 > 360) {
		rotationAngle5 = -360;
	}
	rotationAngle6 += 0.2;
	if (rotationAngle6 > 360) {
		rotationAngle6 = -360;
	}

	// if 's' is pressed to see stars
	if (sparkleStars) {
		// update the interpolation variable 
		interp += interpDif;

		if (interp >= 1.0)
			interp = 0.0;
	}

	// move up
	if (upKey) {
		yPos += 0.001;
	}
	// move down
	if (downKey) {
		yPos -= 0.001;
	}

	// redraw the new state
	glutPostRedisplay();
}

/************************************************************************

	Function:		initializeGL

	Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void) {
	
	// set point size to 2
	glPointSize(2.0);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);
	
	// change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);
	
	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// gluPerspective(fovy, aspect, near, far)
	gluPerspective(20, (float)windowWidth / (float)windowHeight, 0.1, 100);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

/********************************************************************

	Function: main

	Description: Sets up the OpenGL rendering context and the
				 windowing system, then begins display loop.

*********************************************************************/
void main(int argc, char** argv) {

	// print controls
	myControls();

	// initialize the toolkit
	glutInit(&argc, argv);
	// set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// set window size
	glutInitWindowSize(windowWidth, windowHeight);
	// set window position on screen
	glutInitWindowPosition(300, 300);
	// open the screen window
	glutCreateWindow("Solar System");

	// register display function
	glutDisplayFunc(myDisplay);
	// register the idle function
	glutIdleFunc(myIdle);
	// register normal keyboard function
	glutKeyboardFunc(myKeyboard);
	// register special keyboard function
	glutSpecialFunc(specialKeys);
	// register special keyboard up function
	glutSpecialUpFunc(mySpecialKeyboardReleased);

	// initialize the rendering context
	initializeGL();
	// go into a perpetual loop
	glutMainLoop();
}
