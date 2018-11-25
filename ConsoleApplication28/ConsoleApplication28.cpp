#include "player.h"

int main()
{
	bool terminate = false;
	int key;
	
	//Coordinate origin;
	//int BloodPos = 0;  

	player p1(200, 450, 100, 50.0, 50.0, 1, true);
	player p2(600, 450, 100, 450.0, 50.0, 2, true);

	YsSoundPlayer player;
	YsSoundPlayer::SoundData heartbeat;

	YsSoundPlayer::SoundData punch;
	YsSoundPlayer::SoundData kick;
	YsSoundPlayer::SoundData shoot;
	YsSoundPlayer::SoundData knife;


	punch.LoadWav("punch.wav");
	kick.LoadWav("kick.wav");
	shoot.LoadWav("shoot.wav");
	knife.LoadWav("knife.wav");

	player.Start();

	FsOpenWindow(16, 16, 800, 600, 1);
	
	while (!terminate)
	{
		FsPollDevice();
		key = FsInkey();

		if (FSKEY_ESC ==key)
			terminate = true;

		/* Player I*/
		
		if (GetKeyState('D') < 0)
		{
			p1.moveRight();
			p1.judge = 1;
		}
		
		if (GetKeyState('A') < 0)
		{
			p1.moveLeft();
			p1.judge = 0;
		}
			
	
		if (key == FSKEY_Z || p1.punchPos != 0)
		{
			if (p1.state != 2)
			{
				p1.punch();
				player.PlayBackground(punch, true);
			}
		}

		if (key == FSKEY_X || p1.kickPos != 0)
		{
			p1.kick();
			if(p1.downPressed==FALSE)
				player.PlayBackground(kick, true);

		}
		if (key == FSKEY_T)
			p1.showText();

		//if (key == FSKEY_B || BloodPos != 0)
		//{
		//	origin = p1.get_origin();
		//	createBlood(origin, BloodPos);
		//}

		if (key == FSKEY_W || p1.InAir==TRUE)
		{
			p1.Jump(0.5);
		}

		if (key == FSKEY_C)
		{
			p1.bullet_init();
			p1.raise_arm();
			if(player.IsPlaying(shoot)==1)
			{
				player.Stop(shoot);
				cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
			}
			if(p1.state==2)
				player.PlayBackground(shoot, true);
		}
		 
		if (key == FSKEY_1) {            // differentiating states
			p1.state = 1;
		}

		if (key == FSKEY_2) {            
			p1.state = 2;
		}

		if (key == FSKEY_3) {
			p1.state = 3;
		}

		if (p1.raisearm_x() != 0) {        // animation for moving arm up
			p1.raise_arm();
		}
			
		if (GetKeyState('S') < 0)
			p1.downPressed = TRUE;
		else
			p1.downPressed = FALSE;

		/* Player II*/
		if (GetKeyState('L') < 0)
		{
			p2.moveRight();
			p2.judge = 1;
		}

		if (GetKeyState('J') < 0)
		{
			p2.moveLeft();
			p2.judge = 0;
		}

		if (key == FSKEY_B || p2.punchPos != 0)
		{
			if (p2.state != 2)
			{
				p2.punch();
				player.PlayBackground(punch, true);
			}
		}

		if (key == FSKEY_N || p2.kickPos != 0)
		{
			p2.kick();
			if (p2.downPressed == FALSE)
				player.PlayBackground(kick, true);

		}
		if (key == FSKEY_Y)
			p2.showText();

		//if (key == FSKEY_B || BloodPos != 0)
		//{
		//	origin = p1.get_origin();
		//	createBlood(origin, BloodPos);
		//}

		if (key == FSKEY_I || p2.InAir == TRUE)
		{
			p2.Jump(0.5);
		}

		if (key == FSKEY_M)
		{
			p2.bullet_init();
			p2.raise_arm();
			if (player.IsPlaying(shoot) == 1)
			{
				player.Stop(shoot);
				cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
			}
			if (p2.state == 2)
				player.PlayBackground(shoot, true);
		}

		if (key == FSKEY_7) {            // differentiating states
			p2.state = 1;
		}

		if (key == FSKEY_8) {
			p2.state = 2;
		}

		if (key == FSKEY_9) {
			p2.state = 3;
		}

		if (p2.raisearm_x() != 0) {        // animation for moving arm up
			p2.raise_arm();
		}

		if (GetKeyState('K') < 0)
			p2.downPressed = TRUE;
		else
			p2.downPressed = FALSE;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!p1.getIfDie()) {
			//            p1.stand();
			if (p1.state == 1)              // default standing position
				p1.draw();
			else if (p1.state == 2) {       // use shooter position
				p1.laser_position();
				p1.draw_laser();
				p1.laser_move();
			}
			else if (p1.state == 3) {       // use knife position
				p1.knife_position();
			}


			/* Life Part */
			p1.drawLife();
			p1.ifHit(key);
			p1.handleLife();
			p1.checkIfDie(terminate);
		}

		if (!p2.getIfDie()) {
			//            p1.stand();
			if (p2.state == 1)              // default standing position
				p2.draw();
			else if (p2.state == 2) {       // use shooter position
				p2.laser_position();
				p2.draw_laser();
				p2.laser_move();
			}
			else if (p2.state == 3) {       // use knife position
				p2.knife_position();
			}


			/* Life Part */
			p2.drawLife();
			p2.ifHit(key);
			p2.handleLife();
			p2.checkIfDie(terminate);
		}
		FsSleep(20);
		FsSwapBuffers();
	}
}