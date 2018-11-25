#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
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
    
    
    Coordinate laser_traj;
    bool bullet_visible = false;
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
    player(int x, int y, int lv, float lx, float ly, int num, bool main);
    void draw(bool downPressed,bool InAir);
    void moveLeft();
    void moveRight(); // change the origin coordinates, store the new leg coordinates/new config
    
    void punch(int &punchPos); // store the new coordinates for the arm/new config
    void kick(int &kickpos); // store the new coordinates for the leg/new config
    
    bool getIfDie();                                        // Get if die
    void ifHit(int key, int &type_hit, int state);          // Deice if hit
    
    /* Life Methods */
    void drawLife();                                        // Draw the life bar
    void handleLife(int &type_hit);                         // Check the hit points left in time
    void checkIfDie(bool &terminate);                       // Check if the player dies
    Coordinate get_origin() { return StickyManOrigin; }
    void Jump(float dt, float &v, bool &InAir);
    void showText();
    
    
    //void raise_arm();
    
    //void draw_laser();
    //void laser_move();
    //void bullet_init();
    //bool bulletvisible();       // return bullet visible status
    //bool bullet_hit();          // return whether bullet hit
    //int raisearm_x();           // arm position raised
    
    void knife_position(bool downPressed, bool InAir);                      // ADD:draw the knife position
    void laser_position(bool downPressed, bool InAir);                      // ADD:draw the laser position
    
    void draw_lasers();
    void process_lasers();
    void laser_move();
    void start_a_bullet();         //
    //bool bulletvisible();       // return bullet visible status
    bool bullet_hit();          // return whether bullet hit
    int raisearm_x();           // arm position raised
    int bullets_on();           // the number of bullets that are on screen
    void draw_reload();
    void raise_arm();
    
};

void createBlood(Coordinate origin,int &BloodPos);
