#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

using namespace std;

class Menu {
private:
	int width, height, counter;
	double x, y;
	char nickname[20];
public:
	Menu(int w, int h);
	void drawRectangle(double x1, double x2, double y1, double y2); //y1 is the upper y coordinate and
	void drawScreen();											   //y2 is the bottom
	void drawButtons(bool pveOrPvp, bool first, int loopCount, bool pve, bool secondInput);
	void flash(int count);
	void insertLetter(int &pos, char nameLetter);
	void showNickname(int loopCount, int pos, bool ready, bool pve, bool secondInput);
	void saveNickname(int &pos, bool &secondInput, bool pve, bool &terminate);
	void loadNickname(int &pos, bool &ready, bool &secondInput, bool pve, bool &terminate);
};