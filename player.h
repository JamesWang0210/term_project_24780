#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

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
	int X_RightHandJoint_length2;
	int Y_RightHandJoint_length2;
	int X_LeftLegJoint_length;
	int X_RightLeg;
	int X_LeftLeg;
	int Y_LegRight = 50;
	int Y_LegLeft = 50;

};

struct knifeCoordinates {
	int x_righthand_joint;                          // knife, supplementary corrdinates to stickman figure
	int y_righthand_joint;
	int x_knife_bottom;
	int y_knife_bottom;
	int x_knife_tip;
	int y_knife_tip;
	int x_knife_shield_l;
	int y_knife_shield_l;
	int x_knife_shield_r;
	int y_knife_shield_r;

	int x_lefthand;
	int y_lefthand;
	int x_righthand;
	int y_righthand;
};

struct lasers {
	bool isvisible;
	bool bullethit = false; // determine whether hit by a character
	float x;
	float y;
	bool shoot_right;       // 1 default: shoot right; 0 shoot left
};


class player
{
private:
	knifeCoordinates knife;
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

	//bool bullet_visible = false;
	bool bullethit = false; // determine whether hit by a character
	Coordinate guntip;
	Coordinate raisearm;

	lasers b1;
	lasers b2;
	lasers b3;
	lasers b4;
	lasers b5;
	lasers b6;
	lasers bullets[6] = { b1,b2,b3,b4,b5,b6 };             // an array of laser data

public:
	bool bullet_visible = false;
	int judge = 0;
	int judge_gun;
	int state;							// State of the Player

	bool InAir = FALSE;
	bool downPressed = FALSE;
	int type_hit = -1;

	int punchPos = 0;
	int kickPos = 0;

	float v = 50;

    player(int x, int y, int lv, float lx, float ly, int num, bool main);
	void draw();
	void moveLeft();
	void moveRight();							// change the origin coordinates, store the new leg coordinates/new config

	void punch();								// store the new coordinates for the arm/new config
	void kick();								// store the new coordinates for the leg/new config
    
    bool getIfDie();							// Get if die
    void ifHit(int key);						// Deice if hit
    
    /* Life Methods */
    void drawLife();                            // Draw the life bar
    void handleLife();							// Check the hit points left in time
    void checkIfDie(bool &terminate);           // Check if the player dies
	Coordinate get_origin() { return StickyManOrigin; }
	lasers get_origin_laser(int i) { return bullets[i]; }
	void Jump(float dt);
	void showText();


	//Weapon module
	void raise_arm();
	void knife_position();                      // ADD:draw the knife position
	void laser_position();                      // ADD:draw the laser position

	//Lasers section
	void draw_lasers();
	void process_lasers();
	void laser_move();
	void start_a_bullet();
	bool bulletvisible(int i);						// return bullet visible status
	void bullet_hit(int key);							// return whether bullet hit
		int raisearm_x();							// arm position raised
	int bullets_on();           // the number of bullets that are on screen
	void turn_bullet_off(int i);
	//void draw_reload();
	void stab();
};

//void createBlood(Coordinate origin,int &BloodPos);

