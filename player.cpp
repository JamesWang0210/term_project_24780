#include "player.h"

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
}

player::~player()
{
	//cleanUp();
}

/* Drawing */
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

void player::draw()
{
	int rad = 20;
	
	glLineWidth(15);
	glColor3f(0.0, 0.0, 0);
	glBegin(GL_LINES);
    glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
    glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

    glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
    glVertex2i(StickyManOrigin.x+SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);

	glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
	glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);

	glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
	glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length-SC.X_LeftHandJoint_length2, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length+SC.Y_LeftHandJoint_length2);

	glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
	glVertex2i(StickyManOrigin.x + SC.X_RightLeg , StickyManOrigin.y + rad + SC.lenght+SC.Y_LegRight);

	glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
	glVertex2i(StickyManOrigin.x - SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);
    
    glEnd();
    
    glColor3f(1, 0, 0);
    drawCircle(StickyManOrigin, rad, true);

	/*if (SC.X_RightHandJoint_length!=40)
	{
		SC.X_RightHandJoint_length = 40;
		SC.Y_RightHandJoint_length = 30;
	}
	*/
	
}

/* Moving */
void player::moveLeft()
{
	StickyManOrigin.x-= 10;
	if (StickyManOrigin.x < 30)
		StickyManOrigin.x = 30;
	if (SC.X_RightLeg == 30)
		SC.X_RightLeg = -20;
	else
		SC.X_RightLeg = 30;

	if (SC.X_LeftLeg == 30)
		SC.X_LeftLeg = -20;
	else
		SC.X_LeftLeg = 30;

}

void player::moveRight()
{
	StickyManOrigin.x += 10;
	if (StickyManOrigin.x > 770)
		StickyManOrigin.x = 770;
	if (SC.X_RightLeg == 30)
		SC.X_RightLeg = -20;
	else
		SC.X_RightLeg = 30;

	if (SC.X_LeftLeg == 30)
		SC.X_LeftLeg = -20;
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

/**
void player::stand()
{
	load("stand.txt");
}
void player::load(string fName)
{
	//open the file
	ifstream myfile;
	myfile.open(fName);
	//check if it opened
	if (myfile.is_open()) {
		player::cleanUp();
		myfile >> width >> height;
		player::create(width, height);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				myfile >> pixels[(i + 1) * width + j];
			}
		}
		// check if it is the end of the file
		if (myfile.eof()) {

		}
		myfile.close();
	}

}*/

// Decide if hit by someone
void player::ifHit(int key, int &type_hit)
{
    // key: hit type
    // type_hit: 0 for punch, 1 for kick
    
    // Main Player
    if (num_player == 2){
        switch (key)
        {
            case(FSKEY_Z):
                type_hit = 0;
                break;
            case(FSKEY_X):
                type_hit = 1;
                break;
        }
    }
    
    // Enemy 1
    if (num_player == 1){
        switch (key)
        {
            case(FSKEY_N):
                type_hit = 0;
                break;
            case(FSKEY_M):
                type_hit = 1;
                break;
        }
    }
}

/* Life Methods */

// have to initialize static variables of class
const int player::SIDEMAG;

// Draw the life bar
void player::drawLife()
{
    int hp_percent = 100 * lifeValue / life_tot;        // the percent of HP health remaining
    
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
    } else {
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
    
    string life_digit = to_string(lifeValue);           // display HP value
    const char *life_cstr = life_digit.c_str();          // the life HP of player
    
    glColor3ub(32,32,32);
    glRasterPos2i(lifeX, lifeY - 5);
    YsGlDrawFontBitmap12x16("Health:");
    glRasterPos2i(lifeX+1, lifeY - 5);
    YsGlDrawFontBitmap12x16("Health:");
    
    glColor3ub(204, 0, 0);
    glRasterPos2i(lifeX + 88, lifeY-5);
    YsGlDrawFontBitmap12x16(life_cstr);
    glRasterPos2i(lifeX + 89, lifeY - 5);
    YsGlDrawFontBitmap12x16(life_cstr);
    
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
    }
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

// Get id die
bool player::getIfDie(){
    return is_die;
}

/* Attack and Die*/
Coordinate player::getOrigin(){
    return StickyManOrigin;
}
