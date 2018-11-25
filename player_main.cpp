#include "player.h"

int main()
{
	bool terminate = false;
	int key;
	bool InAir = FALSE;
	int type_hit = -1;
	Coordinate origin;
	player p1(100, 50.0, 50.0, 1, true);
	int punchPos = 0;
	int kickpos = 0;
	FsOpenWindow(16, 16, 800, 600, 1);
	int BloodPos = 0;
	float v = 30;
	int state = 1;           // the state of weapon position

	while (!terminate)
	{
		FsPollDevice();
		key = FsInkey();

		if (FSKEY_ESC == key)
			terminate = true;

		if (GetKeyState('D')<0)
			p1.moveRight();

		if (GetKeyState('A') < 0)
			p1.moveLeft();

		if (key == FSKEY_Z || punchPos != 0)
		{
			if (state != 2)
				p1.punch(punchPos);
		}

		if (key == FSKEY_X || kickpos != 0)
		{
			p1.kick(kickpos);

		}
		if (key == FSKEY_T)
			p1.showText();

		if (key == FSKEY_B || BloodPos != 0)
		{
			origin = p1.get_origin();
			createBlood(origin, BloodPos);

		}

		if (key == FSKEY_W || InAir == TRUE)
		{
			p1.Jump(0.5, v, InAir);
		}

		if (key == FSKEY_C && state == 2)
		{
			p1.start_a_bullet();
			//p1.draw_lasers();
			p1.raise_arm();
		}

		if (key == FSKEY_1) {            // differentiating states
			state = 1;
		}

		if (key == FSKEY_2) {
			state = 2;
		}

		if (key == FSKEY_3) {
			state = 3;
		}

		if (p1.raisearm_x() != 0) {        // animation for moving arm up
			p1.raise_arm();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!p1.getIfDie()) {
			//            p1.stand();
			if (state == 1)              // default standing position
				p1.draw();
			else if (state == 2) {       // use shooter position
				p1.laser_position();
				p1.draw_lasers();        //
				p1.laser_move();       //
				p1.process_lasers();
			}
			else if (state == 3) {       // use knife position
				p1.knife_position();
			}


			/* Life Part */
			p1.drawLife();
			p1.ifHit(key, type_hit);
			p1.handleLife(type_hit);
			p1.checkIfDie(terminate);
		}

		//p1.stand();
		//p1.create();n
		//        p1.draw();
		FsSleep(20);
		FsSwapBuffers();
	}
}

