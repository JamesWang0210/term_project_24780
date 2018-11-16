#pragma once

#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

#define PI 3.141592653589793

class Environment {
private:
	int w, h;
public:
	Environment();
	void drawLine(double x1, double y1, double x2, double y2);
	void drawCircle(double x, double y, double radius);
	void drawRectangle(double x1, double x2, double y1, double y2, bool fill); //y1 is the upper y coordinate and
	void draw();												   //y2 is the bottom
};