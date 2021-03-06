
#include "pch.h"
#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <string>
//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <cmath>
#include <vector>

#endif

using namespace std;

class Electron {
private:
	//motion boundries
	float X0 = 80, X1 = 140, Y0 = 26, Y1 = 100;
	char type = 'w'; // w = wire , r = reverse  , d = diode
	int direction;
public:
	float xPos, yPos;
	Electron(float xPos, float yPos, int direction) {
		this->xPos = xPos;
		this->yPos = yPos;
		this->direction = direction;
	}
	void setType(char type) {
		this->type = type;
	}
	void setBoundries(float X0, float X1, float Y0, float Y1) {
		this->X0 = X0;
		this->X1 = X1;
		this->Y0 = Y0;
		this->Y1 = Y1;
	}
	void circulate(float l) {

		if (type == 'd') {
			yPos += l;
			if (yPos > Y1) {
				yPos = Y0;
			}
			return;
		}
		if (type == 'r') {
			yPos -= l;
			if (yPos < Y0) {
				yPos = Y1;
			}
			return;
		}
		switch (direction) {
		case 1: {
			xPos += l;
			if (xPos > X1) {
				xPos = X1;
				direction = 2;
			}
			break;
		}
		case 2: {
			yPos -= l;
			if (yPos < Y0) {
				yPos = Y0;
				direction = 3;
			}
			break;
		}
		case 3: {
			xPos -= l;
			if (xPos < X0) {
				xPos = X0;
				direction = 4;
			}
			break;
		}
		case 4: {
			yPos += l;
			if (yPos > Y1) {
				yPos = Y1;
				direction = 1;
			}
			break;
		}
		}

	}
};

// Flow electrons
vector<Electron> electrons, diodeElectrons, reverseElectrons;
void initElectronsVector() {
	// initializing electrons array
	for (int i = 0; i < 6; i++) {
		electrons.push_back(Electron(80.0f + i * 10, 100.0f, 1));
		electrons.push_back(Electron(140.0f - i * 10, 26.0f, 3));
	}
	for (int i = 0; i < 7; ++i) {
		electrons.push_back(Electron(140.0f, 100.0f - 10 * i, 2));
		electrons.push_back(Electron(80.0f, 26.0f + 10 * i, 4));
	}

	for (int i = 0; i < 5; i++) {
		diodeElectrons.push_back(Electron(90, 37 + 10 * i, 4));
		diodeElectrons[i].setType('d');
		diodeElectrons[i].setBoundries(90, 90, 37, 88);

	}

	for (int i = 0; i < 5; i++) {
		reverseElectrons.push_back(Electron(70, 37 + 10 * i, 4));
		reverseElectrons[i].setType('r');
		reverseElectrons[i].setBoundries(70, 70, 37, 88);

	}

}
void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);

}

float y = 1.0;
void drawVoltLevel(float v) {
	string str = to_string(v);
	glPushMatrix();
	glColor3f(0.73f, 0.16f, 0.96f); //#declare Med_Purple = colour red 0.73 green 0.16 blue 0.96
	glTranslatef(176.0f, 64.0f, 0.0f);
	glScalef(0.05f, 0.09f, -8);

	for (int i = 0; i < 3; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
	}
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'V');
	glutPostRedisplay();
	glPopMatrix();
}
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}
void draw_circuit() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(8.0);
	glBegin(GL_LINES); //---
	glVertex3f(79.0, 100.0, 0.0);
	glVertex3f(141.0, 100.0, 0.0);
	glEnd();

	glBegin(GL_LINES); //|
	glVertex3f(140.0, 100.0, 0.0);
	glVertex3f(140.0, 70.0, 0.0);
	glEnd();
	glBegin(GL_LINES);//--
	glVertex3f(130.0, 70.0, 0.0);
	glVertex3f(150.0, 70.0f, 0.0);
	glEnd();
	glBegin(GL_LINES);//--
	glVertex3f(135.0, 67.0, 0.0);
	glVertex3f(145.0, 67.0, 0.0);
	glEnd();
	glBegin(GL_LINES);//||
	glVertex3f(140.0, 67.0, 0.0);
	glVertex3f(140.0, 26.0, 0.0);
	glEnd();
	glBegin(GL_LINES);//--
	glVertex3f(79.0, 26.0, 0.0);
	glVertex3f(141.0, 26.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(80.0, 100.0, 0.0);
	glVertex3f(80.0, 90.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(80.0, 36.0, 0.0);
	glVertex3f(80.0, 26.0, 0.0);
	glEnd();



}
void draw_polarity() {
	glColor3f(0.73f, 0.16f, 0.96f); //#declare Med_Purple = colour red 0.73 green 0.16 blue 0.96
	// +
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(155.0, 70.0, 0.0);
	glVertex3f(161.0, 70.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(158.0, 72.0, 0.0);
	glVertex3f(158.0, 68.0, 0.0);
	glEnd();
	//-
	glBegin(GL_LINES);
	glVertex3f(155.0, 66.0, 0.0);
	glVertex3f(161.0, 66.0, 0.0);
	glEnd();
}

void draw_VoltBox() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(175.0f, 75.0f, 0.0f);
	glVertex3f(190.0f, 75.0f, 0.0f);
	glVertex3f(190.0f, 60.0f, 0.0f);
	glVertex3f(175.0f, 60.0f, 0.0f);

	glEnd();


}

//Draws regular polygon given the radius of the touching excircle.
void regularPolygon(int noEdges, float radius, float orienationAngle
	, float centX = 0.0f, float centY = 0.0f, float centZ = 0.0f) {

	bool  translated = 0;
	if (!(centX && centY && centZ)) {
		glTranslatef(centX, centY, centZ);
		translated = 1;
	}
	float angle = (2 * 3.14f) / noEdges;
	float x = 0.0f, y = radius;
	float lastX, lastY;

	glRotatef(orienationAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);

	while (noEdges--) {
		glVertex3f(x, y, 0.0f);
		lastX = x; lastY = y;
		x = lastX * cos(angle) + lastY * sin(angle);
		y = -1 * lastX*sin(angle) + lastY * cos(angle);
	}

	glEnd();
	if (translated) glTranslatef(-centX, -centY, -centZ);

}

float depLength = 0.5;
float voltLevel = 1;
int direction = 0; // 1 =up , 0 = down
float delay = 15;
void update(int value) {
	//Electrons flow control
	for (int i = 0; i < electrons.size(); i++) {
		electrons[i].circulate(0.75);
	}

	for (int i = 0; i < diodeElectrons.size(); i++) {
		diodeElectrons[i].circulate(1);
	}

	for (int i = 0; i < reverseElectrons.size(); i++) {
		reverseElectrons[i].circulate(0.25);
	}

	//Volt and Depletion width control
	if (direction == 1 && voltLevel < 1) {
		depLength -= 2;
		voltLevel += 0.2;
		delay /= 1.5;
	}

	if (direction == -1 && voltLevel > 0.4) {
		depLength += 2;
		voltLevel -= 0.2;
		delay *= 1.5;
	}

	direction = 0;

	glutPostRedisplay();
	glutTimerFunc(delay, update, 0);
}

void drawParticles() {
	glPushMatrix();
	glColor3f(0, 0, 1);
	for (int i = 0; i < electrons.size(); ++i) {
		regularPolygon(10, 1.0, 0, electrons[i].xPos, electrons[i].yPos, 0.0);
	}

	for (int i = 0; i < diodeElectrons.size(); ++i) {
		regularPolygon(10, 1.0, 0, diodeElectrons[i].xPos, diodeElectrons[i].yPos, 0.0);
	}

	glPopMatrix();
	glColor3f(25 / 255, 25 / 255, 102 / 255);
	for (int i = 0; i < reverseElectrons.size(); ++i) {
		regularPolygon(10, 1.0, 0, reverseElectrons[i].xPos, reverseElectrons[i].yPos, 0.0);
	}

}
void drawArrowsAndText() {
	//Header
	string str = "Diode forward bias";
	glPushMatrix();
	glColor3f(0.137255f, 0.419608f, 0.556863f); //#declare SteelBlue = color red 0.137255 green 0.419608 blue 0.556863
	glTranslatef(60.0f, 110.0f, 0.0f);
	glScalef(0.09f, 0.09f, -18);

	for (int i = 0; i < str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
	}
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES); //|
	glVertex3f(50.0, 80.0, 0.0);
	glVertex3f(50.0, 60.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(50.0, 58.0, 0.0);
	glVertex3f(48.0, 60.0, 0.0);
	glVertex3f(52.0, 60.0, 0.0);
	glEnd();


	// Text on arrow
	str = "reverse current";
	glColor3f(0.30f, 0.30f, 1.00f); //#declare NeonBlue = color red 0.30 green 0.30 blue 1.00
	glTranslatef(45.0f, 55.0f, 0.0f);
	glScalef(0.05f, 0.04f, -15);
	glRotatef(90, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
	}

	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES); //|
	glVertex3f(105.0, 80.0, 0.0);
	glVertex3f(105.0, 60.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(105.0, 82.0, 0.0);
	glVertex3f(107.0, 80.0, 0.0);
	glVertex3f(103.0, 80.0, 0.0);
	glEnd();
	// Text on arrow
	str = "forward current";
	glTranslatef(110.0f, 55.0f, 0.0f);
	glScalef(0.05f, 0.04f, -15);
	glRotatef(90, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
	}
	glPopMatrix();
}
void draw_AnodeAndcathode() {

	//+ side
	glColor3f(0.737255, 0.560784, 0.560784);
	glBegin(GL_QUADS);
	glVertex3f(60.0f, 90.0f, 0.0f);
	glVertex3f(100.0f, 90.0f, 0.0f);
	glVertex3f(100.0f, 63.0f, 0.0f);
	glVertex3f(60.0f, 63.0f, 0.0f);
	glEnd();
	//-ve side
	glColor3f(0.184314, 0.184314, 0.309804);// #declare MidnightBlue = color red 0.184314 green 0.184314 blue 0.309804
	glBegin(GL_QUADS);
	glVertex3f(60.0f, 63.0f, 0.0f);
	glVertex3f(100.0f, 63.0f, 0.0f);
	glVertex3f(100.0f, 36.0f, 0.0f);
	glVertex3f(60.0f, 36.0f, 0.0f);
	glEnd();



}
void draw_depletionReg(float y) {
	// dep
	//glTranslatef(0.0f, 0.0f, .0f);
	//glScalef(1.0f, y, 0.0f);                        //scale in x & y axis
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);              //change color to orange
	glVertex3f(60.0f, 64.0f + depLength, 0.0f);
	glVertex3f(100.0f, 64.0f + depLength, 0.0f);
	glVertex3f(100.0f, 62.0f - depLength, 0.0f);
	glVertex3f(60.0f, 62.0f - depLength, 0.0f);
	glEnd();

}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glPushMatrix();
	draw_circuit();
	glPopMatrix();

	glPushMatrix();
	draw_polarity();
	glPopMatrix();

	glPushMatrix();
	draw_VoltBox();
	glPopMatrix();

	glPushMatrix();
	draw_polarity();
	glPopMatrix();

	draw_AnodeAndcathode();
	glPushMatrix();
	//glLineWidth(5.0);
	draw_depletionReg(y);
	glutPostRedisplay();
	glPopMatrix();

	glPushMatrix();
	draw_VoltBox();
	glPopMatrix();
	drawParticles();
	drawVoltLevel(voltLevel);
	drawArrowsAndText();
	glFlush();

}

//Called when a key is pressed
void processSpecialKeys(int key, int mx, int my) {

	switch (key) {

	case GLUT_KEY_UP: //increase temp
		direction = 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN: //decrease temp
		direction = -1;
		glutPostRedisplay();
		break;

	default:
		break;
	}


}


int main(int argc, char *argv[])
{
	initElectronsVector();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(25, 100);
	initRendering();
	glutCreateWindow(" Diod Forward Bias ");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutSpecialFunc(processSpecialKeys);
	glutTimerFunc(delay, update, 0);
	glutMainLoop();
	return 0;
}


