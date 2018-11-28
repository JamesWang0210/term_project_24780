#include "environment.h"

Environment::Environment()
{
	w = 800;
	h = 600;
}

void Environment::drawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}

void Environment::drawCircle(double x, double y, double radius)
{
	double angle, xPos, yPos; //x, y and angle are used for drawing the circle in every iteration
	glBegin(GL_POLYGON); //draw circle based on the ball center coordinates
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xPos = x + cos(angle)*(double)radius;
		yPos = y + sin(angle)*(double)radius;
		glVertex2d(xPos, yPos);
	}
	glEnd();
}

void Environment::drawRectangle(double x1, double x2, double y1, double y2, bool fill)
{	//y1 is the upper y coordinate and y2 is the bottom
	if (fill)
		glBegin(GL_QUADS);
	else
		glBegin(GL_LINE_LOOP);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void Environment::draw()
{
	glLineWidth(4);
	/*glColor3ub(255, 128, 0);
	glRasterPos2i(50, 370);
	YsGlDrawFontBitmap20x32("Start");*/
	glColor3ub(0, 0, 0);
	drawRectangle(50, 150, 50, 100, 0); //exit sign
	glColor3ub(0, 153, 0);
	glRasterPos2i(54, 90);
	YsGlDrawFontBitmap20x32("Fight");
	int step = 30;
	glColor3ub(0, 0, 0);
	double splitScreen = h - 1.5 * step * 7;//=285
	drawLine(0, splitScreen, w, splitScreen);
	glBegin(GL_LINE_STRIP); //stairs
	for (int i = 0; i < 7; i++) { //stairs start at x = 320
		glVertex2d(w / 2.5 + 2 * step * i, h - 1.5 * step * i); //stair length = 60
		glVertex2d(w / 2.5 + 2 * step * i, h - 1.5 * step * (i + 1)); // stair height = 45
	}
	glEnd();
	drawRectangle(650, 750, 400, 600, 0); //door
	drawCircle(735, 500, 5); //door knob
	drawLine(400, splitScreen, 400, splitScreen - 80);
	drawLine(500, splitScreen, 500, splitScreen - 80);
	glColor3ub(153, 76, 0);
	glLineWidth(6);
	drawLine(400, splitScreen - 80, 500, splitScreen - 80);
}
