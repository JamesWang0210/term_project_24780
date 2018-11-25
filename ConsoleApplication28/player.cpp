#include "player_1.h"

player::player(int x, int y, int lv, float lx, float ly, int num, bool main)
{
    StickyManOrigin.x = x;
    StickyManOrigin.y = y;
    SC.lenght = 80;
    SC.X_RightHandJoint_length = 40;
    SC.Y_RightHandJoint_length = 30;
    SC.X_LeftHandJoint_length = 20;
    SC.Y_LeftHandJoint_length = 15;
    SC.X_LeftHandJoint_length2=20;
    SC.Y_LeftHandJoint_length2=15;
    SC.X_LeftLeg = 30;
    SC.X_RightLeg = 30;
    SC.Y_LegRight = 50;
    SC.Y_LegLeft = 50;
    
    /* Life Part */
    lifeValue = lv;
    lifeX = lx;
    lifeY = ly;
    frame = lv;
    
    life_tot = lv;
    
    num_player = num;
    is_main = main;
    
    for (int i = 0; i < 6; i++) {
        bullets[i].x = guntip.x;
        bullets[i].y = guntip.y;
        bullets[i].isvisible = false;
    }
}

void drawCircle(Coordinate origin, int rad, bool fill)
{
    const double PI = 3.1415927;
    
    if (fill)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);
    
    int i;
    for (i = 0; i < 64; i++) {
        double angle = (double)i * PI / 32.0;
        double x = (double)origin.x + cos(angle)*(double)rad;
        double y = (double)origin.y + sin(angle)*(double)rad;
        glVertex2d(x, y);
    }
    glEnd();
}

void player::draw(bool downPressed, bool InAir)
{
    int rad = 20;
    if (downPressed == false)
    {
        SC.lenght = 80;
        if(InAir==false)
            StickyManOrigin.y = 450;
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINES);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length - SC.X_LeftHandJoint_length2, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + SC.X_RightLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegRight);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);
        
        glEnd();
    }
    
    else
    {
        float newYOrigin;
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        SC.lenght = 60;
        
        StickyManOrigin.y = 480;
        glBegin(GL_LINES);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length - SC.X_LeftHandJoint_length2, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x + 5, StickyManOrigin.y + rad + SC.lenght + 40);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x - 5, StickyManOrigin.y + rad + SC.lenght + 40);
        
        glEnd();
        
    }
    glColor3f(0, 0, 0);
    drawCircle(StickyManOrigin, rad, true);
}

void player::moveLeft()
{
    StickyManOrigin.x-= 10;
    if (StickyManOrigin.x < 30)
        StickyManOrigin.x = 30;
    if (SC.X_RightLeg == 30)
        SC.X_RightLeg = 20;
    else
        SC.X_RightLeg = 30;
    
    if (SC.X_LeftLeg == 30)
        SC.X_LeftLeg = 20;
    else
        SC.X_LeftLeg = 30;
    
}

void player::moveRight()
{
    StickyManOrigin.x += 10;
    if (StickyManOrigin.x > 770)
        StickyManOrigin.x = 770;
    if (SC.X_RightLeg == 30)
        SC.X_RightLeg = 20;
    else
        SC.X_RightLeg = 30;
    
    if (SC.X_LeftLeg == 30)
        SC.X_LeftLeg = 20;
    else
        SC.X_LeftLeg = 30;
    
}

void player::kick(int &kickpos)
{
    SC.X_RightLeg = 30 + kickpos;
    SC.Y_LegRight = 50 - kickpos;
    kickpos += 5;
    if (kickpos == 50)
    {
        kickpos = 0;
        SC.X_RightLeg = 30;
        SC.Y_LegRight = 50;
    }
}

void player::punch(int &punchPos)
{
    SC.X_RightHandJoint_length = 40+punchPos;
    SC.Y_RightHandJoint_length = 30-punchPos;
    SC.X_LeftHandJoint_length2 = 20 -punchPos;
    SC.Y_LeftHandJoint_length2= 15+ punchPos;
    punchPos += 3;
    if (punchPos == 30)
    {
        punchPos = 0;
        SC.X_RightHandJoint_length = 40;
        SC.Y_RightHandJoint_length = 30;
        SC.X_LeftHandJoint_length2 = 20 ;
        SC.Y_LeftHandJoint_length2 = 15 ;
    }
    
}
// Get id die
bool player::getIfDie(){
    return is_die;
}

// Decide if hit by someone
void player::ifHit(int key, int &type_hit, int state)
{
    // key: hit type
    // type_hit: 0 for punch, 1 for kick
    
    // Main Player
    if (num_player == 2){
        if (key == FSKEY_Z && state == 1)
            type_hit = 0;
        
        if (key == FSKEY_X)
            type_hit = 1;
        
        if (key == FSKEY_C)
            type_hit = 2;
        
        if (key == FSKEY_Z && state == 3)
            type_hit = 3;
    }
    
    // Enemy 1
    //    if (num_player == 1){
    //        switch (key)
    //        {
    //            case(FSKEY_N):
    //                type_hit = 0;
    //                break;
    //            case(FSKEY_M):
    //                type_hit = 1;
    //                break;
    //        }
    //    }
}

// Check the hit points left in time
void player::handleLife(int &type_hit)
{
    switch (type_hit)
    {
        case(0):
            lifeValue -= 1;
            type_hit = -1;
            break;
        case(1):
            lifeValue -= 2;
            type_hit = -1;
            break;
        case(2):
            lifeValue -= 5;
            type_hit = -1;
            break;
        case(3):
            lifeValue -= 3;
            type_hit = -1;
            break;
    }
}

/* Life Methods */

// have to initialize static variables of class
const int player::SIDEMAG;

// Draw the life bar
void player::drawLife()
{
    int hp_percent = (100*lifeValue) / life_tot ;        // the percent of HP health remaining
    //cout << life_tot << endl;
    cout << hp_percent << endl;
    double long_side = lifeValue * SIDEMAG;             // Long Side of Life Bar
    double short_side = 30;
    
    double long_side_1 = frame * SIDEMAG;
    double short_side_1 = 20;
    
    switch (num_player){
        case(1):
            short_side = short_side_1 = 30;             // Short Side of Life Bar
            break;
        case(2):
            short_side = short_side_1 = 20;             // Short Side of Life Bar
            break;
    }
    
    // Vertices for lifebar
    int rbar, gbar, bbar;        // RGB values for the hp bar
    if (hp_percent <= 100 && hp_percent > 50) {
        rbar = 0;
        gbar = 204;
        bbar = 0;
    }
    else if (hp_percent <= 50 && hp_percent > 20) {
        rbar = 255;
        gbar = 165;
        bbar = 0;
    }
    else if (hp_percent <= 20 && hp_percent > 0) {
        rbar = 204;
        gbar = 0;
        bbar = 0;
    }
    else if (hp_percent == 0) {
        rbar = 0;
        gbar = 0;
        bbar = 0;
    }
    
    glColor3ub(rbar, gbar, bbar);                            // Yellow as default
    glBegin(GL_QUADS);                                  // Rectangular Life Bar
    
    glVertex2i(lifeX, lifeY);
    glVertex2i(lifeX + long_side, lifeY);
    glVertex2i(lifeX + long_side, lifeY + short_side);
    glVertex2i(lifeX, lifeY + short_side);
    
    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);                                // Rectangular Life Bar
    
    // Outline for lifebar
    glVertex2i(lifeX, lifeY);
    glVertex2i(lifeX + long_side_1, lifeY);
    glVertex2i(lifeX + long_side_1, lifeY + short_side_1);
    glVertex2i(lifeX, lifeY + short_side_1);
    glEnd();
    
    // HP module
    
    string life_digit = to_string(hp_percent);           // display HP value
    const char *life_cstr = life_digit.c_str();          // the life HP of player
    
    glColor3ub(32,32,32);
    glRasterPos2i(lifeX, lifeY-5);
    YsGlDrawFontBitmap12x16("Health:");
    glRasterPos2i(lifeX+1, lifeY - 5);
    YsGlDrawFontBitmap12x16("Health:");
    
    glColor3ub(204, 0, 0);
    glRasterPos2i(lifeX + 88, lifeY-5);
    YsGlDrawFontBitmap12x16(life_cstr);
    glRasterPos2i(lifeX + 89, lifeY - 5);
    YsGlDrawFontBitmap12x16(life_cstr);
    
}

// Check if the player dies
void player::checkIfDie(bool &terminate)
{
    if (lifeValue <= 0){
        if (is_main)
            terminate = true;
        is_die = true;
    } else {
        is_die = false;
    }
}

// Blood View
void createBlood(Coordinate origin, int &BloodPos)
{
    glLineWidth(3);
    glColor3f(255, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(origin.x + 10+ BloodPos, origin.y-8- BloodPos);
    glVertex2i(origin.x + 14+ BloodPos, origin.y-12 - BloodPos);
    glVertex2i(origin.x , origin.y-8- BloodPos);
    glVertex2i(origin.x , origin.y-12- BloodPos);
    glVertex2i(origin.x - 10 - BloodPos, origin.y-8- BloodPos);
    glVertex2i(origin.x - 14 - BloodPos, origin.y-12- BloodPos);
    glVertex2i(origin.x + 20+ BloodPos, origin.y - 28- BloodPos);
    glVertex2i(origin.x + 24+ BloodPos, origin.y - 32- BloodPos);
    glVertex2i(origin.x, origin.y - 28- BloodPos);
    glVertex2i(origin.x, origin.y - 32- BloodPos);
    glVertex2i(origin.x - 20- BloodPos, origin.y - 28- BloodPos);
    glVertex2i(origin.x - 24- BloodPos, origin.y - 32- BloodPos);
    //drawCircle(origin,100, true);
    //glEnd();
    glFlush();
    BloodPos++;
    if (BloodPos == 10)
        BloodPos = 0;
}

// Jump Action
void player::Jump(float dt,float &v, bool &InAir)
{
    StickyManOrigin.y = StickyManOrigin.y - 0.5*(9.80)*(dt*dt) - v* dt;
    v = v + (-9.80)*dt;
    InAir = true;
    if (StickyManOrigin.y >= 450)
    {
        StickyManOrigin.y = 450;
        InAir = false;
        v = 50;
    }
}

// Text View
void player::showText()
{
    glColor3f(256, 0, 0);                            // Yellow as default
    glBegin(GL_QUADS);                                  // Rectangular Life Bar
    
    glVertex2i(StickyManOrigin.x - 200, StickyManOrigin.y - 50);
    glVertex2i(StickyManOrigin.x + 250, StickyManOrigin.y - 50);
    glVertex2i(StickyManOrigin.x + 250, StickyManOrigin.y-80);
    glVertex2i(StickyManOrigin.x - 200, StickyManOrigin.y - 80);
    
    glEnd();
    glColor3ub(1, 1, 0);
    glRasterPos2i(StickyManOrigin.x-200, StickyManOrigin.y-50);
    YsGlDrawFontBitmap20x32("Show me what you've got");
    FsSwapBuffers();
    FsSleep(1000);
}

void player::knife_position(bool downPressed, bool InAir)
{
    int rad = 20;
    if (downPressed == false)
    {
        
        if (InAir == false)
            StickyManOrigin.y = 450;
        
        SC.lenght = 80;
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINES);
        
        //body
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        //right arm setup
        double ratio = 0.4;   // need to check integer input
        knife.x_righthand_joint = StickyManOrigin.x + SC.X_RightHandJoint_length*ratio - 1; // store the number in struct
        knife.y_righthand_joint = StickyManOrigin.y + rad + SC.Y_RightHandJoint_length*ratio + 4;
        //right upper arm
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);
        
        //right lower arm
        knife.x_righthand = knife.x_righthand_joint + SC.X_RightHandJoint_length*(1 - ratio - 0.2);
        knife.y_righthand = knife.y_righthand_joint - SC.Y_RightHandJoint_length*(ratio - 0.2);
        
        glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);
        glVertex2i(knife.x_righthand, knife.y_righthand);
        
        //left upper arm
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        
        //left lower arm
        knife.x_lefthand = StickyManOrigin.x - SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2 - 8;
        knife.y_lefthand = StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2;
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        glVertex2i(knife.x_lefthand, knife.y_lefthand);
        
        
        //right leg
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + SC.X_RightLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegRight);
        
        //left leg
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);
    }
    else
    {
        StickyManOrigin.y = 480;
        SC.lenght = 60;
        
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINES);
        
        //body
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        //right arm setup
        double ratio = 0.4;   // need to check integer input
        knife.x_righthand_joint = StickyManOrigin.x + SC.X_RightHandJoint_length*ratio - 1; // store the number in struct
        knife.y_righthand_joint = StickyManOrigin.y + rad + SC.Y_RightHandJoint_length*ratio + 4;
        //right upper arm
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);
        
        //right lower arm
        knife.x_righthand = knife.x_righthand_joint + SC.X_RightHandJoint_length*(1 - ratio - 0.2);
        knife.y_righthand = knife.y_righthand_joint - SC.Y_RightHandJoint_length*(ratio - 0.2);
        
        glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);
        glVertex2i(knife.x_righthand, knife.y_righthand);
        
        //left upper arm
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        
        //left lower arm
        knife.x_lefthand = StickyManOrigin.x - SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2 - 8;
        knife.y_lefthand = StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2;
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
        glVertex2i(knife.x_lefthand, knife.y_lefthand);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x + 5, StickyManOrigin.y + rad + SC.lenght + 40);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x - 5, StickyManOrigin.y + rad + SC.lenght + 40);
    }
    glEnd();
    
    glColor3f(0, 0, 0);
    drawCircle(StickyManOrigin, rad, true);
    
    //Draw knife
    glLineWidth(11);
    glColor3ub(34, 0, 204);
    glBegin(GL_LINES);
    
    
    knife.x_knife_bottom = knife.x_righthand - 8;
    knife.y_knife_bottom = knife.y_righthand + 4;
    knife.x_knife_tip = knife.x_righthand + 18;     // can use this coordinate to determine knife damange
    knife.y_knife_tip = knife.y_righthand - 9;
    knife.x_knife_shield_l = knife.x_righthand - 4;
    knife.y_knife_shield_l = knife.y_righthand - 5;
    knife.x_knife_shield_r = knife.x_righthand + 4;
    knife.y_knife_shield_r = knife.y_righthand + 5;
    
    glVertex2i(knife.x_knife_bottom, knife.y_knife_bottom);
    glVertex2i(knife.x_knife_tip, knife.y_knife_tip);
    
    glVertex2i(knife.x_knife_shield_l, knife.y_knife_shield_l);
    glVertex2i(knife.x_knife_shield_r, knife.y_knife_shield_r);
    glEnd();
    
}

void player::laser_position(bool downPressed, bool InAir) {
    int rad = 20;
    if (downPressed == false)
    {
        SC.lenght = 80;
        if (InAir == false)
            StickyManOrigin.y = 450;
        
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINES);
        
        //body
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        //right arm setup
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
        glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length - 5 + raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);
        
        //left upper arm
        int adjust = 5;   // based on the default stickerman figure
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + adjust);
        
        //left lower arm
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + adjust);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2 - 5, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2 + adjust);
        
        //right leg setup
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + SC.X_RightLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegRight);
        
        //left leg
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);
        
        glEnd();
        
        glColor3f(0, 0, 0);
        drawCircle(StickyManOrigin, rad, true);
        
        //draw gun
        glShadeModel(GL_SMOOTH);
        glLineWidth(16);
        glColor3ub(0, 0, 255);
        glBegin(GL_LINES);
        
        int gunwidth = 20;
        int right_hand_x = StickyManOrigin.x + SC.X_RightHandJoint_length - 5 + raisearm.x;
        int right_hand_y = StickyManOrigin.y + rad + 10 + raisearm.y;
        
        // lower end of gun
        glVertex2i(right_hand_x, right_hand_y + 7);
        glColor3ub(0, 204, 255);
        glVertex2i(right_hand_x, right_hand_y - 7);
        
        // gun tube
        guntip.y = right_hand_y - 7;
        guntip.x = right_hand_x + gunwidth;
        glColor3ub(0, 204, 0);
        glVertex2i(right_hand_x, guntip.y);
        glColor3ub(204, 204, 0);
        glVertex2i(guntip.x, guntip.y);
        glEnd();
        
        //trigger
        glLineWidth(13);
        glColor3ub(152, 153, 255);
        glBegin(GL_LINES);
        int length = 6;
        glVertex2i(right_hand_x - length, right_hand_y - 8 - length - raisearm.y);
        glVertex2i(right_hand_x, right_hand_y - 8);
    }
    else
    {
        SC.lenght = 60;
        StickyManOrigin.y = 480;
        
        glLineWidth(15);
        glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINES);
        
        //body
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        
        //right arm setup
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
        glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length - 5 + raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);
        
        //left upper arm
        int adjust = 5;   // based on the default stickerman figure
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + adjust);
        
        //left lower arm
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + adjust);
        glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2 - 5, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2 + adjust);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x + 5, StickyManOrigin.y + rad + SC.lenght + 40);
        
        glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        
        glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
        glVertex2i(StickyManOrigin.x - 5, StickyManOrigin.y + rad + SC.lenght + 40);
        
        glEnd();
        
        glColor3f(0, 0, 0);
        drawCircle(StickyManOrigin, rad, true);
        
        //draw gun
        glShadeModel(GL_SMOOTH);
        glLineWidth(16);
        glColor3ub(0, 0, 255);
        glBegin(GL_LINES);
        
        int gunwidth = 20;
        int right_hand_x = StickyManOrigin.x + SC.X_RightHandJoint_length - 5 + raisearm.x;
        int right_hand_y = StickyManOrigin.y + rad + 10 + raisearm.y;
        
        // lower end of gun
        glVertex2i(right_hand_x, right_hand_y + 7);
        glColor3ub(0, 204, 255);
        glVertex2i(right_hand_x, right_hand_y - 7);
        
        // gun tube
        guntip.y = right_hand_y - 7;
        guntip.x = right_hand_x + gunwidth;
        glColor3ub(0, 204, 0);
        glVertex2i(right_hand_x, guntip.y);
        glColor3ub(204, 204, 0);
        glVertex2i(guntip.x, guntip.y);
        glEnd();
        
        //trigger
        glLineWidth(13);
        glColor3ub(152, 153, 255);
        glBegin(GL_LINES);
        int length = 6;
        glVertex2i(right_hand_x - length, right_hand_y - 8 - length - raisearm.y);
        glVertex2i(right_hand_x, right_hand_y - 8);
    }
    glEnd();
    
}

void player::draw_lasers() {
    // loop through the vector
    for (int i = 0; i < 6; i++)
    {
        if (bullets[i].isvisible == true) {
            cout << bullets[i].x << endl;
            glLineWidth(40);
            glColor3ub(255, 0, 255);
            glBegin(GL_LINES);
            glVertex2i(bullets[i].x - 20, bullets[i].y);
            glVertex2i(bullets[i].x, bullets[i].y);
            glEnd();
        }
    }
    
}

void player::process_lasers() {
    for (int i = 0; i < 6; i++)
    {
        //cout << "move once" << endl;
        if ((bullets[i].x > 800) || (bullets[i].x < 0) || (bullets[i].bullethit == true)) {
            bullets[i].isvisible = false;
        }
    }
    
}

void player::laser_move() {
    for (int i = 0; i < 6; i++) {
        if (bullets[i].isvisible == true) {
            bullets[i].x += 15;
        }
    }
}

int player::bullets_on() {
    int num = 0;
    for (int i = 0; i < 6; i++) {
        if (bullets[i].isvisible == true) {
            num += 1;
        }
    }
    return num;
}

void player::start_a_bullet() {
    for (int i = 0; i < 6; i++) {
        //&& bullets[i].x == guntip.x && bullets[i].y == guntip.y
        if (bullets[i].isvisible == false) {
            bullets[i].isvisible = true;
            bullets[i].x = guntip.x - raisearm.x;
            bullets[i].y = guntip.y - raisearm.y;
            cout << "One bullet on" << endl;
            break;
        }
    }
}

void player::raise_arm() {
    raisearm.x += -1;
    raisearm.y += -1;
    if (raisearm.x < -6) {
        raisearm.x = raisearm.y = 0;
    }
}

void player::draw_reload() {
    if (bullets_on() == 6) {
        //draw reload figure
    }
    
}

bool player::bullet_hit() {
    return bullethit;
}

int player::raisearm_x() {
    return raisearm.x;
}


