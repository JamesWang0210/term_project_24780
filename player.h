#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <time.h>

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


class player
{
protected:
	Coordinate StickyManOrigin;
	StickyManCoordinates SC;
	knifeCoordinates knife;

    
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
    player(int x, int y, int lv, float lx, float ly, int num, bool main);
	~player();
    
	void draw();
	void moveLeft();
	void moveRight(); // change the origin coordinates, store the new leg coordinates/new config

	void punch(int &punchPos); // store the new coordinates for the arm/new config
	void kick(int &kickpos); // store the new coordinates for the leg/new config
    /* Life Methods */
    void drawLife();                            // Draw the life bar
    void handleLife(int &type_hit);             // Check the hit points left in time
    void checkIfDie(bool &terminate);           // Check if the player dies
    
    /* Attack and Die*/
    Coordinate getOrigin();                     // Get origin of the player
    bool getIfDie();                            // Get if die
    void ifHit(int key, int &type_hit);         // Deice if hit

	Coordinate laser_traj;
	bool bullet_visible = false;
	bool bullethit = false; // determine whether hit by a character
	Coordinate guntip;
	Coordinate raisearm;


	void raise_arm();
	void knife_position();                      // ADD:draw the knife position
	void laser_position();                      // ADD:draw the laser position
	void draw_laser();
	void laser_move();
	void bullet_init();

    
};


