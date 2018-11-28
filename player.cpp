#include "player.h"

player::player(int x, int y, int lv, float lx, float ly, int num, bool main)
{
	StickyManOrigin.x = x;
	StickyManOrigin.y = y;
	SC.lenght = 80;
	SC.X_RightHandJoint_length = 20;
	SC.Y_RightHandJoint_length = 15;
	SC.X_LeftHandJoint_length = 20;
	SC.Y_LeftHandJoint_length = 15;
	SC.X_LeftHandJoint_length2= 20;
	SC.Y_LeftHandJoint_length2= 15;
	SC.X_RightHandJoint_length2 = 20;
	SC.Y_RightHandJoint_length2 = 15;
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

	state = 1;
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

void player::draw()
{	
	int rad = 20;
	if (downPressed == FALSE)
	{
		SC.lenght = 80;
		if(InAir==FALSE)
			StickyManOrigin.y = 450;
		glLineWidth(10);
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

		//add;
		glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);
		glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + SC.Y_RightHandJoint_length2);

		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
		glVertex2i(StickyManOrigin.x + SC.X_RightLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegRight);

		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
		glVertex2i(StickyManOrigin.x - SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);

		glEnd();
	}
	
	else
	{
		float newYOrigin;
		glLineWidth(10);
		glColor3f(0.0, 0.0, 0);
		SC.lenght = 40;

		StickyManOrigin.y = 500;
		glBegin(GL_LINES);
		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);

		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);

		glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
		glVertex2i(StickyManOrigin.x - SC.X_LeftHandJoint_length - SC.X_LeftHandJoint_length2, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2);

		glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length);
		glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + SC.Y_RightHandJoint_length2);

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

void player::moveLeft(int speed)
{
	StickyManOrigin.x-= speed;
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

void player::moveRight(int speed)
{
	StickyManOrigin.x += speed;
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

void player::kick()
{
	//SC.X_RightLeg = 30 + kickpos;
	//SC.Y_LegRight = 50 - kickpos;
	//kickpos += 5;
	//if (kickpos == 50)
	//{
	//	kickpos = 0;
	//	SC.X_RightLeg = 30;
	//	SC.Y_LegRight = 50;
	//}

	if (judge == 1)
	{
		SC.X_RightLeg = 30 + kickPos;
		SC.Y_LegRight = 50 - kickPos;
		kickPos += 5;
		if (kickPos == 50)
		{
			kickPos = 0;
			SC.X_RightLeg = 30;
			SC.Y_LegRight = 50;
		}
	}

	if (judge == 0)
	{
		SC.X_LeftLeg = 30 + kickPos;
		SC.Y_LegLeft = 50 - kickPos;
		kickPos += 5;
		if (kickPos == 50)
		{
			kickPos = 0;
			SC.X_LeftLeg = 30;
			SC.Y_LegLeft = 50;
		}
	}
}

void player::punch(bool &InAction1,bool &InAction2)
{
	/*SC.X_RightHandJoint_length = 40+punchPos;
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
	}*/
	if (judge == 1)
	{
		cout << "action1=" << InAction1 << endl;
		if (InAction2 == true)
		{
			cout << "ttttttttttttttttttttttttttttttttttttt";
			InAction2 = false;
			SC.X_RightHandJoint_length2 = 20 + punchPos;
			SC.Y_RightHandJoint_length2 = 15 - punchPos;
			SC.X_RightHandJoint_length = 20 + punchPos / 3;
			SC.Y_RightHandJoint_length = 15 - punchPos / 3;
			SC.X_LeftHandJoint_length2 = 20 - punchPos;
			SC.Y_LeftHandJoint_length2 = 15 + punchPos;

		}
		InAction1 = true;
		SC.X_RightHandJoint_length2 = 20 + punchPos;
		SC.Y_RightHandJoint_length2 = 15 - punchPos;
		SC.X_RightHandJoint_length = 20 + punchPos/3;
		SC.Y_RightHandJoint_length = 15 - punchPos/3;
		SC.X_LeftHandJoint_length2 = 20 - punchPos;
		SC.Y_LeftHandJoint_length2 = 15 + punchPos;
		punchPos += 3;
		if (punchPos == 30)
		{
			punchPos = 0;
			InAction1 = false;
			cout << "action1=" << InAction1 << endl;
			SC.X_RightHandJoint_length = 20;
			SC.Y_RightHandJoint_length = 15;
			SC.X_RightHandJoint_length2 = 20;
			SC.Y_RightHandJoint_length2 = 15;
			SC.X_LeftHandJoint_length2 = 20;
			SC.Y_LeftHandJoint_length2 = 15;
		}
	}

	if (judge == 0)
	{
		if (InAction1 == true)
		{
			cout << "yyyyyyyyyyyyyyyyyyyyyyyyy" << endl;
			InAction1 = false;
			SC.X_RightHandJoint_length = 20;
			SC.Y_RightHandJoint_length = 15;
			SC.X_RightHandJoint_length2 = 20;
			SC.Y_RightHandJoint_length2 = 15;
			SC.X_LeftHandJoint_length2 = 20;
			SC.Y_LeftHandJoint_length2 = 15;
		}
		InAction2 = true;
		SC.X_LeftHandJoint_length2 = 20 + punchPos;
		SC.Y_LeftHandJoint_length2 = 15 - punchPos;
		SC.X_LeftHandJoint_length = 20 + punchPos/3;
		SC.Y_LeftHandJoint_length = 15 - punchPos/3;
		SC.X_RightHandJoint_length2 = 20 - punchPos;
		SC.Y_RightHandJoint_length2 = 15 + punchPos;
		punchPos += 3;
		if (punchPos == 30)
		{
			InAction2 = false;
			punchPos = 0;
			SC.X_LeftHandJoint_length2 = 20;
			SC.Y_LeftHandJoint_length2 = 15;
			SC.X_RightHandJoint_length2 = 20;
			SC.Y_RightHandJoint_length2 = 15;
			SC.X_LeftHandJoint_length = 20;
			SC.Y_LeftHandJoint_length = 15;
		}
	}
}

void player::stab() {

	SC.X_RightHandJoint_length2 = 20 + punchPos / 2;
	SC.Y_RightHandJoint_length2 = 15 - punchPos / 2;
	SC.X_RightHandJoint_length = 20 + punchPos * 1.2;
	SC.Y_RightHandJoint_length = 15 - punchPos * 0.35;
	SC.X_LeftHandJoint_length2 = 20 - punchPos / 2;
	SC.Y_LeftHandJoint_length2 = 15 + punchPos / 2;
	punchPos += 3;

	if (punchPos == 30)
	{
		punchPos = 0;
		SC.X_RightHandJoint_length = 20;
		SC.Y_RightHandJoint_length = 15;
		SC.X_RightHandJoint_length2 = 20;
		SC.Y_RightHandJoint_length2 = 15;
		SC.X_LeftHandJoint_length2 = 20;
		SC.Y_LeftHandJoint_length2 = 15;
	}
}
// Get id die
bool player::getIfDie(){
    return is_die;
}

// Decide if hit by someone
void player::ifHit(int key, int s)
{
    // key: hit type
    // type_hit: 0 for punch, 1 for kick
    
    // Main Player
    if (num_player == 2){
		if (key == FSKEY_Z && s == 1)
			type_hit = 0;

		if (key == FSKEY_X)
			type_hit = 1;

		/*if (key == FSKEY_C && state == 2)
			type_hit = 2;*/

		if (key == FSKEY_Z && s == 3)
			type_hit = 3;
    }
    
    // Enemy 1
	else if (num_player == 1){
		if (key == FSKEY_B && s == 1)
			type_hit = 0;

		if (key == FSKEY_N)
			type_hit = 1;

		/*if (key == FSKEY_M && state == 2)
			type_hit = 2;*/

		if (key == FSKEY_B && s == 3)
			type_hit = 3;
	}
}


// Check the hit points left in time
void player::handleLife()
{
	switch (type_hit)
	{
	case(0) :
		lifeValue -= 1;
		type_hit = -1;
		break;
	case(1) :
		lifeValue -= 2;
		type_hit = -1;
		break;
	case(2) :
		lifeValue -= 5;
		type_hit = -1;
		break;
	case(3) :
		lifeValue -= 3;
		type_hit = -1;
		break;
	}
}

/* Life Methods */

// have to initialize static variables of class
//const int player::SIDEMAG;

// Draw the life bar
void player::drawLife()
{
    int hp_percent = (100*lifeValue) / life_tot ;        // the percent of HP health remaining
	//cout << life_tot << endl;
	//cout << hp_percent << endl;
    double long_side = lifeValue * SIDEMAG;             // Long Side of Life Bar
    double short_side = 25;
    
    double long_side_1 = frame * SIDEMAG;
    double short_side_1 = 25;
    
    //switch (num_player){
    //    case(1):
    //        short_side = short_side_1 = 30;             // Short Side of Life Bar
    //        break;
    //    case(2):
    //        short_side = short_side_1 = 20;             // Short Side of Life Bar
    //        break;
    //}
    
    // Vertices for lifebar
    int rbar, gbar, bbar;        // RGB values for the hp bar
    if (hp_percent <= 100 && hp_percent > 70) {
        rbar = 0;
        gbar = 204;
        bbar = 0;
    }
    else if (hp_percent <= 70 && hp_percent > 25) {
        rbar = 255;
        gbar = 165;
        bbar = 0;
    }
    else if (hp_percent <= 25 && hp_percent > 0) {
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
    
	glLineWidth(5);
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
void player::checkIfDie(bool &terminate, string playerName)
{
    if (lifeValue <= 0){
		glColor3ub(1, 1, 0);
		glRasterPos2i(200, 300);
		if (playerName == "left")
		{
			YsGlDrawFontBitmap20x32("Player Right Wins!!!!");
			FsSwapBuffers();
			FsSleep(2000);
		}
		else
		{
			YsGlDrawFontBitmap20x32("Player Left Wins!!!!");
			FsSwapBuffers();
			FsSleep(2000);
		}
		FsSleep(1000);
		terminate = true;
        is_die = true;
    } else {
        is_die = false;
    }
	
}

void player::createBlood(Coordinate origin)
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
	//drawCircle(origin,100, TRUE);
	glEnd();
	//glFlush();
	BloodPos++;
	if (BloodPos == 10)
		BloodPos = 0;

}

void player::Jump(float dt)
{
	StickyManOrigin.y = StickyManOrigin.y - 0.5*(9.80)*(dt*dt) - v* dt;
	v = v + (-9.80)*dt;
	InAir = TRUE;
	if (StickyManOrigin.y >= 450)
	{
		StickyManOrigin.y = 450;
		InAir = FALSE;
		v = 50;
	}
}

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

void player::knife_position()
{


	int rad = 20;

	glLineWidth(15);
	glColor3f(0.0, 0.0, 0);
	glBegin(GL_LINES);

	if (judge == 1) {
		//right arm setup
		//double ratio = 1.4;   // need to check integer input;
		knife.x_righthand_joint = StickyManOrigin.x + SC.X_RightHandJoint_length*0.8 - 1; // store the number in struct
		knife.y_righthand_joint = StickyManOrigin.y + rad + SC.Y_RightHandJoint_length*0.8 + 4;
		//right upper arm
		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);

		//right lower arm
		knife.x_righthand = knife.x_righthand_joint + SC.X_RightHandJoint_length2 - 7;
		knife.y_righthand = knife.y_righthand_joint - (SC.Y_RightHandJoint_length2 - 7);

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

		if (downPressed == FALSE)
		{
			if (InAir == FALSE)
				StickyManOrigin.y = 450;
			SC.lenght = 80;

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

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

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			// legs
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
	else if (judge == 0) {
		//right arm setup
		//double ratio = 1.4;   // need to check integer input;
		knife.x_righthand_joint = StickyManOrigin.x - SC.X_RightHandJoint_length*0.8 + 1; // store the number in struct
		knife.y_righthand_joint = StickyManOrigin.y + rad + SC.Y_RightHandJoint_length*0.8 + 4;
		//right upper arm
		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);

		//right lower arm
		knife.x_righthand = knife.x_righthand_joint - SC.X_RightHandJoint_length2 + 7;
		knife.y_righthand = knife.y_righthand_joint - (SC.Y_RightHandJoint_length2 - 7);

		glVertex2i(knife.x_righthand_joint, knife.y_righthand_joint);
		glVertex2i(knife.x_righthand, knife.y_righthand);

		//left upper arm
		glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
		glVertex2i(StickyManOrigin.x + SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);

		//left lower arm
		knife.x_lefthand = StickyManOrigin.x + SC.X_LeftHandJoint_length - SC.X_LeftHandJoint_length2 + 8;
		knife.y_lefthand = StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length + SC.Y_LeftHandJoint_length2;
		glVertex2i(StickyManOrigin.x + SC.X_LeftHandJoint_length, StickyManOrigin.y + rad + SC.Y_LeftHandJoint_length);
		glVertex2i(knife.x_lefthand, knife.y_lefthand);

		if (downPressed == FALSE)
		{
			if (InAir == FALSE)
				StickyManOrigin.y = 450;
			SC.lenght = 80;

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			//right leg
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
			glVertex2i(StickyManOrigin.x - SC.X_RightLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegRight);

			//left leg
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
			glVertex2i(StickyManOrigin.x + SC.X_LeftLeg, StickyManOrigin.y + rad + SC.lenght + SC.Y_LegLeft);
		}
		else
		{
			StickyManOrigin.y = 480;
			SC.lenght = 60;

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			// legs
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
			glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);

			glVertex2i(StickyManOrigin.x - 15, StickyManOrigin.y + rad + SC.lenght + 20);
			glVertex2i(StickyManOrigin.x - 5, StickyManOrigin.y + rad + SC.lenght + 40);

			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);
			glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);

			glVertex2i(StickyManOrigin.x + 15, StickyManOrigin.y + rad + SC.lenght + 20);
			glVertex2i(StickyManOrigin.x + 5, StickyManOrigin.y + rad + SC.lenght + 40);
		}
		glEnd();

		glColor3f(0, 0, 0);
		drawCircle(StickyManOrigin, rad, true);

		//Draw knife
		glLineWidth(11);
		glColor3ub(34, 0, 204);
		glBegin(GL_LINES);


		knife.x_knife_bottom = knife.x_righthand + 8;
		knife.y_knife_bottom = knife.y_righthand + 4;
		knife.x_knife_tip = knife.x_righthand - 18;     // can use this coordinate to determine knife damange
		knife.y_knife_tip = knife.y_righthand - 9;
		knife.x_knife_shield_l = knife.x_righthand + 4;
		knife.y_knife_shield_l = knife.y_righthand - 5;
		knife.x_knife_shield_r = knife.x_righthand - 4;
		knife.y_knife_shield_r = knife.y_righthand + 5;

		glVertex2i(knife.x_knife_bottom, knife.y_knife_bottom);
		glVertex2i(knife.x_knife_tip, knife.y_knife_tip);

		glVertex2i(knife.x_knife_shield_l, knife.y_knife_shield_l);
		glVertex2i(knife.x_knife_shield_r, knife.y_knife_shield_r);
		glEnd();
	}

}

void player::laser_position() {
	int rad = 20;
	if (downPressed == FALSE)
	{
		if (judge == 1)
		{
			SC.lenght = 80;
			if (InAir == FALSE)
				StickyManOrigin.y = 450;

			glLineWidth(15);
			glColor3f(0.0, 0.0, 0);
			glBegin(GL_LINES);

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			//right arm setup
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
			glVertex2i(StickyManOrigin.x + (SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2) - 5 + raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);

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
			int right_hand_x = StickyManOrigin.x + (SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2) - 5 + raisearm.x;
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
			SC.lenght = 80;
			if (InAir == FALSE)
				StickyManOrigin.y = 450;

			glLineWidth(15);
			glColor3f(0.0, 0.0, 0);
			glBegin(GL_LINES);

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			//right arm setup
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
			glVertex2i(StickyManOrigin.x - (SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2) + 5 - raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);

			//left upper arm
			int adjust = 5;   // based on the default stickerman figure

			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + adjust);

			//left lower arm
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + adjust);
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length - SC.X_RightHandJoint_length2 - 5, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + SC.Y_RightHandJoint_length2 + adjust);

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
			int left_hand_x = StickyManOrigin.x - (SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2) + 5 - raisearm.x;
			int left_hand_y = StickyManOrigin.y + rad + 10 + raisearm.y;

			// lower end of gun
			glVertex2i(left_hand_x, left_hand_y + 7);
			glColor3ub(0, 204, 255);
			glVertex2i(left_hand_x, left_hand_y - 7);

			// gun tube
			guntip.y = left_hand_y - 7;
			guntip.x = left_hand_x - gunwidth;
			glColor3ub(0, 204, 0);
			glVertex2i(left_hand_x, guntip.y);
			glColor3ub(204, 204, 0);
			glVertex2i(guntip.x, guntip.y);
			glEnd();

			//trigger
			glLineWidth(13);
			glColor3ub(152, 153, 255);
			glBegin(GL_LINES);
			int length = 6;
			glVertex2i(left_hand_x + length, left_hand_y - 8 - length - raisearm.y);
			glVertex2i(left_hand_x, left_hand_y - 8);
		}
	}

	else
	{
		if (judge == 1)
		{
			SC.lenght = 40;
			StickyManOrigin.y = 500;

			glLineWidth(15);
			glColor3f(0.0, 0.0, 0);
			glBegin(GL_LINES);

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			//right arm setup
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
			glVertex2i(StickyManOrigin.x + (SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2) - 5 + raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);

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
			int right_hand_x = StickyManOrigin.x + (SC.X_RightHandJoint_length + SC.X_RightHandJoint_length2) - 5 + raisearm.x;
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
			SC.lenght = 40;
			StickyManOrigin.y = 500;

			glLineWidth(15);
			glColor3f(0.0, 0.0, 0);
			glBegin(GL_LINES);

			//body
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + SC.lenght);

			//right arm setup
			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad + 10);
			glVertex2i(StickyManOrigin.x - (SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2) + 5 - raisearm.x, StickyManOrigin.y + rad + 10 + raisearm.y);

			//left upper arm
			int adjust = 5;   // based on the default stickerman figure

			glVertex2i(StickyManOrigin.x, StickyManOrigin.y + rad);
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + adjust);

			//left lower arm
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + adjust);
			glVertex2i(StickyManOrigin.x + SC.X_RightHandJoint_length - SC.X_RightHandJoint_length2 + 5, StickyManOrigin.y + rad + SC.Y_RightHandJoint_length + SC.Y_RightHandJoint_length2 + adjust);

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
			int left_hand_x = StickyManOrigin.x - (SC.X_LeftHandJoint_length + SC.X_LeftHandJoint_length2) + 5 - raisearm.x;
			int left_hand_y = StickyManOrigin.y + rad + 10 + raisearm.y;

			// lower end of gun
			glVertex2i(left_hand_x, left_hand_y + 7);
			glColor3ub(0, 204, 255);
			glVertex2i(left_hand_x, left_hand_y - 7);

			// gun tube
			guntip.y = left_hand_y - 7;
			guntip.x = left_hand_x - gunwidth;
			glColor3ub(0, 204, 0);
			glVertex2i(left_hand_x, guntip.y);
			glColor3ub(204, 204, 0);
			glVertex2i(guntip.x, guntip.y);
			glEnd();

			//trigger
			glLineWidth(13);
			glColor3ub(152, 153, 255);
			glBegin(GL_LINES);
			int length = 6;
			glVertex2i(left_hand_x + length, left_hand_y - 8 - length - raisearm.y);
			glVertex2i(left_hand_x, left_hand_y - 8);
		}
	}
	glEnd();
}

void player::bullet_init()
{
	if (!bullet_visible) 
	{
		laser_traj.x = guntip.x;
		laser_traj.y = guntip.y;
		bullet_visible = true;
		judge_gun = judge;
	}
}


void player::draw_laser() 
{
	if (bullet_visible) 
	{
		glLineWidth(40);
		glColor3ub(255, 0, 255);
		glBegin(GL_LINES);
		glVertex2i(laser_traj.x - 20, laser_traj.y);
		glVertex2i(laser_traj.x, laser_traj.y);
		glEnd();
	}
}

void player::laser_move() 
{
	if (bullet_visible) {
		if (judge_gun == 1) {
			laser_traj.x += 15;
		}   // the speed of laser
		else if (judge_gun == 0) {
			laser_traj.x -= 15;
		}

		//cout << "move once" << endl;
		if ((laser_traj.x > 800) || (laser_traj.x < 0) || (bullethit == true))
			bullet_visible = false;
	}
	/*void player::laser_move() {
		for (int i = 0; i < 6; i++) {
			if (bullets[i].isvisible == true) {
				if (bullets[i].shoot_right == 1) {
					bullets[i].x += 15;
				}
				else if (bullets[i].shoot_right == 0) {
					bullets[i].x -= 15;
				}
			}
		}*/
}


void player::raise_arm() {
	raisearm.x += -1;
	raisearm.y += -1;
	if (raisearm.x < -6) {
		raisearm.x = raisearm.y = 0;
	}
}
bool player::bulletvisible() {
	return bullet_visible;

}

void player::bullet_hit(int key) {
	//cout << abs(laser_traj.x - StickyManOrigin.x) << "\n";
	if (num_player == 2)
	{
		if (key == FSKEY_C && state == 2)
		{
			if (abs(laser_traj.x - StickyManOrigin.x) <= 40 && abs(laser_traj.y - StickyManOrigin.y) <= 85)
			{
				bullet_visible = false;
				type_hit = 2;

			}
		}
	}

	if (num_player == 1)
	{
		if (key == FSKEY_M && state == 2)
		{
			if (abs(laser_traj.x - StickyManOrigin.x) <= 40 && abs(laser_traj.y - StickyManOrigin.y) <= 85)
			{
				bullet_visible = false;
				type_hit = 2;

			}
		}
	}


	
}

int player::raisearm_x() {
	return raisearm.x;
}