#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include "yspng.h"
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
	int groundOriginY;
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
	int x_lefthand_joint;
	int y_lefthand_joint;
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
private:
	knifeCoordinates knife;
	Coordinate StickyManOrigin;
	StickyManCoordinates SC;

	/* Life Variables */
	static const int SIDEMAG = 3;

	int life_tot;
	int yState;
	float r, g, b;

	double lifeValue;                  // Original Hit Points that the Player has
	int num_player = 1;             // # of the Player
	double lifeX, lifeY;            // Position of Life Bar on the Window
	double frame;
	bool is_main;                   // Whether it is the main player

	bool is_die = false;            // Whether the player die
	bool change1State;
	bool change2States;

	Coordinate laser_traj;
	//bool bullet_visible = false;
	bool bullethit = false; // determine whether hit by a character
	Coordinate guntip;
	Coordinate raisearm;
	bool isPve;

public:
	bool InAction1 = false, InAction2 = false;
	bool InAction1_kick = false, InAction2_kick = false;
	bool bullet_visible = false;
	int judge = 0;
	int judge_gun;
	int state;                            // State of the Player

	bool InAir = false;
	bool downPressed = false;
	int type_hit = -1;

	int punchPos = 0;
	int kickPos = 0;

	float v = 50;

	int BloodPos = 0;

	player(int x, int y, double lv, double lx, double ly, int num, bool main, float r_in, float g_in, float b_in, bool pve);
	void draw();
	void moveLeft(int speed);
	void moveRight(int speed);                            // change the origin coordinates, store the new leg coordinates/new config

	void punch();                                // store the new coordinates for the arm/new config
	void kick();                                // store the new coordinates for the leg/new config

	bool getIfDie();                        // Deice if hit
	void ifHit(int key, int state, bool press);
	/* Life Methods */
	void drawLife();                            // Draw the life bar
	void handleLife();                            // Check the hit points left in time
	void checkIfDie(bool &terminate, string playerName, bool pve);           // Check if the player dies
	Coordinate get_origin() { return StickyManOrigin; }
	Coordinate get_origin_laser() { return laser_traj; }

	void set_origin(int a, int b) {             // Going DOWN Yufan
		StickyManOrigin.x = a; StickyManOrigin.y = b;
	}
	void set_ystate(int a) {
		yState = a;                             // 
	}

	void Jump(float dt);
	void showText();


	void raise_arm();
	void knife_position();                      // ADD:draw the knife position
	void laser_position();                      // ADD:draw the laser position
	void draw_laser();
	void laser_move();
	void bullet_init();
	bool bulletvisible();                        // return bullet visible status
	void bullet_hit(int key);                            // return whether bullet hit
	int raisearm_x();                            // arm position raised
	void stab();

	void createBlood(Coordinate origin);
	void getYstate();

	void checkIfWin(bool &terminate, int num);
};

class enemy {
private:

protected:

public:
	player* e1;
	enemy() { e1 = new player(600, 450, 10, 600.0, 50.0, 2, false, 64.0, 64.0, 128.0, true); }

	bool is_die = false;                        // Decide if hit
};