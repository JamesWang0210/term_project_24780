#include "menu.h"

Menu::Menu(int w, int h)
{
	width = w;
	height = h;
	counter = 1;
}

void Menu::drawRectangle(double x1, double x2, double y1, double y2)
{   //y1 is the upper y coordinate and y2 is the bottom
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void Menu::drawScreen() //needs to take width and height 
{					   //of the window as arguments
	glColor3ub(255, 255, 255);
	drawRectangle(0, width, 0, 600);
	glColor3ub(0, 0, 0);
	glRasterPos2i(width / 4, height / 6);
	YsGlDrawFontBitmap20x32("Fighting Stick - Man");
}

void Menu::drawButtons(bool pveOrPvp, bool first, int loopCount, bool pve, bool secondInput)
{
	if (first)
		flash(loopCount);
	else
		glColor3ub(128, 128, 128);
	drawRectangle(width / 3.2, width / 1.4, height / 3, height / 2.5); //draws New Player button
	if (!first)
		flash(loopCount);
	else
		glColor3ub(128, 128, 128);
	drawRectangle(width / 3.2, width / 1.4, height / 3 + 50, height / 2.5 + 50); //draws Existing Player button
	glColor3ub(0, 0, 0);
	if (pveOrPvp) {
		glRasterPos2i(width / 2.7, height / 2.55);
		YsGlDrawFontBitmap20x32("Single Player");
	}
	else {
		if (pve == false) {
			if (secondInput) {
				glRasterPos2i(width / 2.5, height / 3.5);
				YsGlDrawFontBitmap20x32("Player 2");
			}
		}
		glRasterPos2i(width / 2.5, height / 2.55);
		YsGlDrawFontBitmap20x32("New Player");
	}
	if (pveOrPvp)
	{
		glRasterPos2i(width / 2.6, height / 2.1);
		YsGlDrawFontBitmap20x32("Multiplayer");
	}
	else
	{
		if (pve == false) {
			if (secondInput == false) {
				glRasterPos2i(width / 2.5, height / 3.5);
				YsGlDrawFontBitmap20x32("Player 1");
			}
		}
		glRasterPos2i(width / 3, height / 2.1);
		YsGlDrawFontBitmap20x32("Existing Player");
	}
}

void Menu::flash(int count) //alternates between grey and orange
{						   //if a button is selected
	if (count >= 25)
		glColor3ub(128, 128, 128);
	else
		glColor3ub(255, 128, 0);
}

void Menu::insertLetter(int &pos, char nameLetter)
{
	if (pos >= 1 && nameLetter == 55) { //implementing the Backspace function
		nickname[pos - 1] = ' ';
		nickname[pos] = ' ';
		pos -= 1;
	}
	else if (nameLetter != 55) {
		nickname[pos] = nameLetter + 85; //add letter to the nicknamae
		pos += 1;
	}
}

void Menu::showNickname(int loopCount, int pos, bool ready, bool pve, bool secondInput)
{
	if (loopCount >= 25) //simulate the flashing cursor
		nickname[pos] = '_';
	else
		nickname[pos] = ' ';

	glRasterPos2i(width / 16, height / 2.55);
	YsGlDrawFontBitmap20x32("Insert nickname:");
	glRasterPos2i(width / 2.1, height / 2.55);
	YsGlDrawFontBitmap20x32(nickname); //show typed nickname so far
	if (pve == false) {
		if (secondInput) {
			glRasterPos2i(width / 2.5, height / 3.5);
			YsGlDrawFontBitmap20x32("Player 2");
		}
		else {
			glRasterPos2i(width / 2.5, height / 3.5);
			YsGlDrawFontBitmap20x32("Player 1");
		}
	}
	if (ready == false) {
		glRasterPos2i(800 / 16, 600 / 2);
		YsGlDrawFontBitmap20x32("Nickname not found.");
	}
}

void Menu::saveNickname(int &pos, bool &secondInput, bool pve, bool &terminate, string &name1, string &name2)
{
	ofstream outputFile;
	outputFile.open("highscores.txt", ios::app); //open the file in append mode
	//check if it opened
	if (outputFile.is_open()) {
		for (int i = 0; i < pos; i++)
			outputFile << nickname[i];
		outputFile << " " << 0 << endl; //eventually a score will take height's place
	}
	else
		cout << "Unable to open file";
	outputFile.close();
	string Name(nickname);
	if (secondInput) {
		if (pos == 0)
			name2 = "Player 2";
		else
			name2 = Name.substr(0, pos);
	}
	else {
		if (pos == 0)
			name1 = "Player 1";
		else
			name1 = Name.substr(0, pos);
	}
	for (int i = 0; i < 20; i++)
		nickname[i] = ' ';
	pos = 0;
	if (pve)
		terminate = true;
	else
		if (secondInput)
			terminate = true;
	if (secondInput == false)
		secondInput = true;
}

void Menu::loadNickname(int &pos, bool &ready, bool &secondInput, bool pve, bool &terminate, string &name1, string &name2)
{
	ready = false;
	char name[20];
	int j, score, numberOfLines = 0;
	bool *nameExists;
	//string name;
	ifstream inputFile;
	ofstream outputFile;
	string line, nameFromFile;
	string strName(nickname);
	string correctName = strName.substr(0, pos);
	inputFile.open("highscores.txt");
	while (getline(inputFile, line))
		++numberOfLines;
	inputFile.close();
	nameExists = new bool[numberOfLines];
	inputFile.open("highscores.txt"); //open file
	outputFile.open("temp.txt");
	//check if it opened
	if (inputFile.is_open()) {
		if (!inputFile.eof()) {
			for (j = 0; j < numberOfLines; j++) {
				nameExists[j] = false;
				inputFile >> nameFromFile;
				outputFile << nameFromFile;
				if (nameFromFile == correctName) {
					nameExists[j] = true;
					if (secondInput)
						name2 = correctName;
					else
						name1 = correctName;
					inputFile >> score;
					outputFile << " " << 1 << endl; //the current highscore will get the place of 1000 
				}
				else {
					inputFile >> score; //hight will turn to highscore
					outputFile << " " << score << endl;
				}
			}
		}
		inputFile.close();
		outputFile.close();
		ifstream inputFile("temp.txt", ios::binary); //copy temp.txt contents to highlights.txt
		ofstream outputFile("highscores.txt", ios::binary);
		outputFile << inputFile.rdbuf();
		for (j = 0; j < numberOfLines; j++) {
			if (nameExists[j]) {
				ready = true;
				break;
			}
		}
	}
	for (int i = 0; i < 20; i++)
		nickname[i] = ' ';
	pos = 0;
	if (pve == true && ready == true)
		terminate = true;
	else
		if (secondInput && ready)
			terminate = true;
	if (secondInput == false && ready == true)
		secondInput = true;
}

void Menu::instruction()
{
	int w1 = width / 4;
	double s1 = 1.8;
	double i = 0;
	double m = 16;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap12x16("Instructions: ");
	i += 2 * m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Player 1: ");
	i += 2 * m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Move left: A");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Move right: D");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Jump: W");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Crouch: S");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Punch / Knife Hit: Z");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Kick: X");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Shoot: C");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Normal Mode: 1");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Shooting Mode: 2");
	i += m;

	glRasterPos2i(w1, height / s1 + i);
	YsGlDrawFontBitmap8x12("Knife Mode: 3");
	i += m;

	int w2 = width / 1.8;
	double s2 = s1;
	i = 2 * m;
	//m = 0.04;

	/*glRasterPos2i(w2, height / i);
	YsGlDrawFontBitmap8x12("Instructions: ");
	i -= 2 * m;*/

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Player 2: ");
	i += 2 * m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Move left: J");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Move right: L");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Jump: I");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Crouch: K");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Punch / Knife Hit: B");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Kick: N");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Shoot: M");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Normal Mode: 7");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Shooting Mode: 8");
	i += m;

	glRasterPos2i(w2, height / s2 + i);
	YsGlDrawFontBitmap8x12("Knife Mode: 9");
	i += m;
}