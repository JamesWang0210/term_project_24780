#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

using namespace std;

struct Coordinate
{
	float x;
	float y;
};

struct StickyManCoordinates
{
	int lenght;
	int X_RightHandJoint_length;
	int Y_RightHandJoint_length;
	int X_LeftHandJoint_length;
	int Y_LeftHandJoint_length;
	int X_LeftHandJoint_length2;
	int Y_LeftHandJoint_length2;
	int X_LeftLegJoint_length;
	int X_RightLeg;
	int X_LeftLeg;
	int Y_LegRight = 50;
	int Y_LegLeft = 50;

};
class player
{
private:
	//int oriX, oriY, height, width;
	//char *pixels;
	Coordinate StickyManOrigin;
	StickyManCoordinates SC;
    
    /* Life Variables */
    static const int SIDEMAG = 3;
    
    int life_tot;
    
    int lifeValue;                  // Original Hit Points that the Player has
    int num_player = 1;             // # of the Player
    double lifeX, lifeY;            // Position of Life Bar on the Window
    double frame;
    bool is_main;                   // Whether it is the main player
    
    bool is_die = false;            // Whether the player die
public:
    player(int lv, float lx, float ly, int num, bool main);
	~player();
	void draw();
	void create();
	//void cleanUp();
	//char getPixel(int x, int y) const;
	void moveLeft();
	void moveRight(); // change the origin coordinates, store the new leg coordinates/new config

	void punch(int &punchPos); // store the new coordinates for the arm/new config
	void kick(int &kickpos); // store the new coordinates for the leg/new config
	//void stand(); // store the new coords for stand config
	//void load(string fName); // load the config
    
    bool getIfDie();                            // Get if die
    void ifHit(int key, int &type_hit);         // Deice if hit
    
    /* Life Methods */
    void drawLife();                            // Draw the life bar
    void handleLife(int &type_hit);             // Check the hit points left in time
    void checkIfDie(bool &terminate);           // Check if the player dies
	Coordinate get_origin() { return StickyManOrigin; }
	void Jump(float dt, float &v, bool &InAir);
	void showText();

};

void createBlood(Coordinate origin,int &BloodPos);


