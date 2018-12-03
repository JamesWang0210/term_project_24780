#include "player.h"

#include "menu.h"

#include "environment.h"
#include "yspng.h"


void drawPNG(int wid,int hei, GLuint texId) {
	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);
	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_QUADS);

	// For each vertex, assign texture coordinate before vertex coordinate.
	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(400, 0);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(400, 400);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, 400);

	glEnd();
}

int main()

{
	YsRawPngDecoder png[3];
	png[0].Decode("boxer.png");
	png[1].Decode("cartoongun.png");
	png[2].Decode("knife.png");
	bool terminateMenu = false, first = true, pve = true, secondInput = false;

	bool pveOrPvp = true, showButtons = false, ready = true;

	int key, pos = 0, loopCount = 0;

	Menu theMenu(800, 600);

	FsOpenWindow(16, 16, 800, 600, 1);

	// prepare PNG
	GLuint texId[3];  // this will be use as texture identifiers for the two PNGs
					  // glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way.
	for (int i = 0;i < 3;i++) {
		glGenTextures(1, &texId[i]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D, texId[i]);  // Making the texture identifier current (or bring it to the deck)

												 // set up parameters for the current texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D
		(GL_TEXTURE_2D,
			0,    // Level of detail
			GL_RGBA,
			png[i].wid,
			png[i].hei,
			0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			png[i].rgba);
	}

	while (!terminateMenu)

	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		theMenu.drawScreen();

		if (pveOrPvp)

			theMenu.drawButtons(pveOrPvp, first, loopCount, pve, secondInput);

		if (showButtons)

			theMenu.drawButtons(pveOrPvp, first, loopCount, pve, secondInput);

		key = FsInkey();

		switch (key)

		{

		case(FSKEY_ESC):

			terminateMenu = true;

			break;

		case(FSKEY_UP): //change selected button if UP is hit

			if (first)

				first = false;

			else

				first = true;

			break;

		case(FSKEY_DOWN): //change selected button if DOWN is hit

			if (first)

				first = false;

			else

				first = true;

			break;

		case(FSKEY_ENTER): //move to next screen

			if (pveOrPvp) {

				if (first)

					pve = true;

				else

					pve = false;

				pveOrPvp = false;

				showButtons = true;

				first = true;

			}

			else

				if (showButtons) {

					showButtons = false;

					break;

				}

			if (!showButtons && !pveOrPvp) {

				if (first) {

					theMenu.saveNickname(pos, secondInput, pve, terminateMenu);

				}

				else {

					theMenu.loadNickname(pos, ready, secondInput, pve, terminateMenu);

				}

				if (pve == false && ready == true)

					showButtons = true;

			}

		default:

			if (!showButtons && !pveOrPvp) {

				if (12 <= key && key <= 37 || key == 55) //maybe allow numbers

					theMenu.insertLetter(pos, key);

				theMenu.showNickname(loopCount, pos, ready, pve, secondInput);

			}

		}



		FsPollDevice();

		FsSleep(20);

		FsSwapBuffers();

		loopCount += 1;

		if (loopCount == 50)

			loopCount = 0;

	}



	bool terminate = false;

	string playerName;

	bool InAction1 = false;

	bool InAction2 = false;

	bool Cpressed = false;

	bool Mpressed = false;

	//Coordinate origin;

	//int BloodPos = 0;  



	player p1(200, 450, 100, 50.0, 50.0, 1, true);

	player p2(600, 450, 100, 450.0, 50.0, 2, true);

	Environment theEnvironment;

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

	while (!terminate)

	{

		FsPollDevice();

		key = FsInkey();


		if (FSKEY_ESC == key)

			terminate = true;



		/* Player I*/



		if (GetKeyState('D') < 0)

		{

			p1.moveRight(10);

			p1.judge = 1;

		}



		if (GetKeyState('A') < 0)

		{

			p1.moveLeft(10);

			p1.judge = 0;

		}





		if (key == FSKEY_Z || p1.punchPos != 0)

		{

			if (p1.state != 2)

			{

				if (p1.state == 1) {

					p1.punch(InAction1, InAction2);

					player.PlayBackground(punch, true);

				}

				else if (p1.state == 3) {

					p1.stab();

					player.PlayBackground(knife, true);

				}

			}

		}



		if (key == FSKEY_X || p1.kickPos != 0)

		{

			p1.kick();

			if (p1.downPressed == FALSE)

				player.PlayBackground(kick, true);



		}

		if (key == FSKEY_T)

			p1.showText();



		//if (key == FSKEY_B || BloodPos != 0)

		//{

		//	origin = p1.get_origin();

		//	createBlood(origin, BloodPos);

		//}



		if (key == FSKEY_W || p1.InAir == TRUE)

		{

			p1.Jump(0.5);

		}



		if (key == FSKEY_C)

		{

			p1.bullet_init();

			p1.raise_arm();

			if (player.IsPlaying(shoot) == 1)

			{

				player.Stop(shoot);

				//cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;

			}

			if (p1.state == 2)

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

			p2.moveRight(10);

			p2.judge = 1;

		}



		if (GetKeyState('J') < 0)

		{

			p2.moveLeft(10);

			p2.judge = 0;

		}



		if (key == FSKEY_B || p2.punchPos != 0)

		{

			if (p2.state != 2)

			{

				if (p2.state == 1) {

					p2.punch(InAction1, InAction2);

					player.PlayBackground(punch, true);

				}

				else if (p2.state == 3) {

					p2.stab();

					player.PlayBackground(knife, true);

				}

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

				//cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;

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

		int wid, hei;
		FsGetWindowSize(wid, hei);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw PNG
		theEnvironment.draw();

		glViewport(0, 0, wid, hei);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		int size = 40;
		switch (p1.state) {
		case (1):
			glBindTexture(GL_TEXTURE_2D, texId[0]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(50, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(50 + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(50+size, 80+size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(50, 80+size);
			glEnd();
			break;
		case(2):
			glBindTexture(GL_TEXTURE_2D, texId[1]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(50, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(50 + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(50 + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(50, 80 + size);
			glEnd();
			break;
		case(3):
			glBindTexture(GL_TEXTURE_2D, texId[2]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(50, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(50 + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(50 + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(50, 80 + size);
			glEnd();
			break;
		}

		int p2x = 710;
		switch (p2.state) {
		case (1):
			glBindTexture(GL_TEXTURE_2D, texId[0]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(p2x, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(p2x + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(p2x + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(p2x, 80 + size);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case(2):
			glBindTexture(GL_TEXTURE_2D, texId[1]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(p2x, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(p2x + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(p2x + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(p2x, 80 + size);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case(3):
			glBindTexture(GL_TEXTURE_2D, texId[2]);
			glBegin(GL_QUADS);
			// For each vertex, assign texture coordinate before vertex coordinate.
			glTexCoord2d(0.0, 0.0);
			glVertex2i(p2x, 80);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(p2x + size, 80);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(p2x + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(p2x, 80 + size);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		}


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





		}



		/*if (abs(p1.get_origin().x - p2.get_origin().x) <= 100)

		{

		p1.ifHit(key);

		p1.handleLife();

		playerName = "left";

		p1.checkIfDie(terminate, playerName);



		p2.ifHit(key);

		p2.handleLife();

		playerName = "right";

		p2.checkIfDie(terminate, playerName);

		}*/

		if (p1.get_origin().x - p2.get_origin().x <= 100 && p1.get_origin().x - p2.get_origin().x >= 0)// p1 is on the right

		{

			if (key == FSKEY_B || key == FSKEY_N)

			{

				if (p2.judge == 1) // p2 is facing right

				{

					p1.ifHit(key, p2.state);

					p1.moveRight(5);



					p1.handleLife();

					p1.checkIfDie(terminate, "left");



					p2.handleLife();

					p2.checkIfDie(terminate, "right");



					p1.createBlood(p1.get_origin());

				}

			}



			if (key == FSKEY_Z || key == FSKEY_X)

			{

				if (p1.judge == 0) // p1 is facing left

				{

					p2.ifHit(key, p1.state);

					p2.moveLeft(5);





					p1.handleLife();

					p1.checkIfDie(terminate, "left");



					p2.handleLife();

					p2.checkIfDie(terminate, "right");



					p2.createBlood(p2.get_origin());

				}

			}





		}

		else if (p1.get_origin().x - p2.get_origin().x >= -100 && p1.get_origin().x - p2.get_origin().x <= 0)// p1 is on the left

		{

			if (key == FSKEY_B || key == FSKEY_N)

			{

				if (p2.judge == 0) // p2 is facing right

				{

					p1.ifHit(key, p2.state);

					p1.moveLeft(5);



					p1.handleLife();

					p1.checkIfDie(terminate, "left");



					p2.handleLife();

					p2.checkIfDie(terminate, "right");



					p1.createBlood(p1.get_origin());

				}

			}



			if (key == FSKEY_Z || key == FSKEY_X)

			{

				if (p1.judge == 1) // p1 is facing left

				{

					p2.ifHit(key, p1.state);

					p2.moveRight(5);





					p1.handleLife();

					p1.checkIfDie(terminate, "left");



					p2.handleLife();

					p2.checkIfDie(terminate, "right");



					p2.createBlood(p2.get_origin());

				}

			}



		}

		else

		{

			//cout << abs(p1.get_origin_laser().y - p2.get_origin().y) << "\n";

			//cout << p2.type_hit << "\n";



			if (key == FSKEY_C || Cpressed)

			{



				Cpressed = true;

				int xMin = p2.get_origin().x - 10;

				int xMax = p2.get_origin().x + 10;

				int yMin = p2.get_origin().y - 10;

				int yMax = p2.get_origin().y + 90;

				if ((p1.get_origin_laser().x - xMin) >= 0 && (p1.get_origin_laser().x - xMax) <= 0

					&& (p1.get_origin_laser().y - yMin) >= 0 && (p1.get_origin_laser().y - yMax) <= 0)

				{

					p1.bullet_visible = false;

					p2.type_hit = 2;

					p2.createBlood(p2.get_origin());

					Cpressed = false;

				}

			}

			p1.handleLife();

			playerName = "left";

			p1.checkIfDie(terminate, playerName);



			if (key == FSKEY_M || Mpressed)

			{

				Mpressed = true;

				int xMin = p1.get_origin().x - 10;

				int xMax = p1.get_origin().x + 10;

				int yMin = p1.get_origin().y - 10;

				int yMax = p1.get_origin().y + 90;

				if ((p2.get_origin_laser().x - xMin) >= 0 && (p2.get_origin_laser().x - xMax) <= 0

					&& (p2.get_origin_laser().y - yMin) >= 0 && (p2.get_origin_laser().y - yMax) <= 0)

				{

					p2.bullet_visible = false;

					p1.type_hit = 2;

					p1.createBlood(p1.get_origin());

					Mpressed = false;

				}

			}

			p2.handleLife();

			playerName = "right";

			p2.checkIfDie(terminate, playerName);

		}



		FsSleep(20);

		FsSwapBuffers();

	}



}
