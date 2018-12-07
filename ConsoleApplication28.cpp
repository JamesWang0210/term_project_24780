#include "player.h"
#include "menu.h"
#include "environment.h"

void drawPNG(int wid, int hei, GLuint texId) {
	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	// enable texture mappingB
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
	bool terminate = false;
	bool pveOrPvp = true, showButtons = false, ready = true;
	int key, pos = 0, loopCount = 0;
	int prob = rand() % 50 + 1;
	Menu theMenu(800, 600);

	int num = 0;

	GLuint texId[3];

	FsOpenWindow(16, 16, 800, 600, 1);

	// =============================================MENU================================================
	while (!terminateMenu)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theMenu.drawScreen();
		if (pveOrPvp)
		{
			theMenu.drawButtons(pveOrPvp, first, loopCount, pve, secondInput);
			theMenu.instruction();
		}
		if (showButtons)
		{
			theMenu.drawButtons(pveOrPvp, first, loopCount, pve, secondInput);
			theMenu.instruction();
		}
		key = FsInkey();

		switch (key)
		{
		case(FSKEY_ESC):
			terminateMenu = true;
			terminate = true;
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

	string playerName;
	bool InAction1 = false;
	bool InAction2 = false;
	bool Cpressed = false;
	bool Mpressed = false;
	//Coordinate origin;
	//int BloodPos = 0;
	int flag = 0;
	bool flag_last = false;

	player p1(200, 450, 100, 50.0, 50.0, 1, true, 0.0, 0.0, 0.0, pve);
	player p2(600, 450, 100, 450.0, 50.0, 2, false, 128.0, 128.0, 255.0, pve);
	enemy e;
	Environment theEnvironment;
	YsSoundPlayer sound;
	YsSoundPlayer::SoundData heartbeat;

	YsSoundPlayer::SoundData punch;
	YsSoundPlayer::SoundData kick;
	YsSoundPlayer::SoundData shoot;
	YsSoundPlayer::SoundData knife;

	punch.LoadWav("punch.wav");
	kick.LoadWav("kick.wav");
	shoot.LoadWav("shoot.wav");
	knife.LoadWav("knife.wav");

	sound.Start();

	// ========================================SINGLEPLAYER============================================
	while (!terminate && pve)
	{
		FsPollDevice();
		key = FsInkey();

		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
			
		case FSKEY_D:
			p1.moveRight(20);
			p1.judge = 1;
			break;

		case FSKEY_A:
			p1.moveLeft(20);
			p1.judge = 0;
			break;

		case FSKEY_Z: 
			if (p1.state != 2)
			{
				if (p1.state == 1) {
					p1.punch();
					sound.PlayBackground(punch, true);
				}
				else if (p1.state == 3) {
					p1.stab();
					sound.PlayBackground(knife, true);
				}
			}
			break;

		case FSKEY_X:
			if (p1.downPressed == false)
			{
				sound.PlayBackground(kick, true);
				p1.kick();
			}
			break;

		case FSKEY_T:
			p1.showText();
			break;

		case FSKEY_W:
			p1.Jump(0.5);
			break;

		case FSKEY_C:
			p1.bullet_init();
			p1.raise_arm();
			if (sound.IsPlaying(shoot) == 1)
			{
				sound.Stop(shoot);
			}
			if (p1.state == 2)
			{
				sound.PlayBackground(shoot, true);
			}
			break;

		case FSKEY_1:
			p1.state = 1;
			break;

		case FSKEY_2:
			p1.state = 2;
			break;

		case FSKEY_3:
			p1.state = 3;
			break;

		case FSKEY_S:
			p1.downPressed = true;
			break;

		default:
			p1.downPressed = false;
			break;
		}
		/*if (FSKEY_ESC == key)
			terminate = true;*/

		/* Player I*/

	/*	if (key == FSKEY_D)
		{
			p1.moveRight(20);
			p1.judge = 1;
		}*/

		//if (key == FSKEY_A)
		//{
		//	p1.moveLeft(20);
		//	p1.judge = 0;
		//}

		/*if (key == FSKEY_Z || p1.punchPos != 0)
		{
			if (p1.state != 2)
			{
				if (p1.state == 1) {
					p1.punch();
					sound.PlayBackground(punch, true);
				}
				else if (p1.state == 3) {
					p1.stab();
					sound.PlayBackground(knife, true);
				}
			}
		}*/

		/*if (key == FSKEY_X || p1.kickPos != 0)
		{
			if (p1.downPressed == false)
			{
				sound.PlayBackground(kick, true);
				p1.kick();
			}

		}*/
		/*if (key == FSKEY_T)
			p1.showText();*/

		//if (key == FSKEY_W || p1.InAir == true)
		//{
		//	p1.Jump(0.5);
		//}

		/*if (key == FSKEY_C)
		{
			p1.bullet_init();
			p1.raise_arm();
			if (sound.IsPlaying(shoot) == 1)
			{
				sound.Stop(shoot);
			}
			if (p1.state == 2)
			{
				sound.PlayBackground(shoot, true);
			}
		}*/

		//if (key == FSKEY_1) {            // differentiating states
		//	p1.state = 1;
		//}

		//if (key == FSKEY_2) {
		//	p1.state = 2;
		//}

		//if (key == FSKEY_3) {
		//	p1.state = 3;
		//}

		if (p1.raisearm_x() != 0) {        // animation for moving arm up
			p1.raise_arm();
		}

		/*if (key == FSKEY_S)
			p1.downPressed = true;
		else
			p1.downPressed = false;*/

		if (p1.downPressed == false && p1.kickPos != 0)
		{
			sound.PlayBackground(kick, true);
			p1.kick();
		}

		if (p1.InAir == true)
			p1.Jump(0.5);

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theEnvironment.draw();

		if (e.e1->getIfDie())
		{
			if (e.e1 != nullptr) {
				delete[] e.e1;
				e.e1 = nullptr;
				e.is_die = true;
				num += 1;
			}
			else {
				//
			}
		}

		if (!p1.getIfDie()) {
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

		if (!e.is_die) {
			//            p1.stand();
			if (e.e1->state == 1)              // default standing position
				e.e1->draw();
			else if (e.e1->state == 2) {       // use shooter position
				e.e1->laser_position();
				e.e1->draw_laser();
				e.e1->laser_move();
			}
			else if (e.e1->state == 3) {       // use knife position
				e.e1->knife_position();
			}
			/* Life Part */
			e.e1->drawLife();

			// Boss following control
			if (p1.get_origin().x - e.e1->get_origin().x > 100) // p1 is on the right, boss will follow and move to the right
			{
				e.e1->moveRight(5);
				e.e1->judge = 1;
			}

			if (p1.get_origin().x - e.e1->get_origin().x < -100) // p1 is on the left, boss will follow and move to the left
			{
				e.e1->moveLeft(5);
				e.e1->judge = 0;
			}

			// Boss fighting control

			if (80 <= flag)
				flag_last = true;

			if (p1.get_origin().x - e.e1->get_origin().x <= 100 
				&& p1.get_origin().x - e.e1->get_origin().x >= 0 
				&& abs(p1.get_origin().y - e.e1->get_origin().y) < 100)// p1 is on the right
			{
				if (double(prob) / 50 < 0.4) // boss punch
				{
					// Punch
					if (e.e1->punchPos != 0 || flag_last) {
						e.e1->punch();
						sound.PlayBackground(punch, true);
						// Kick
						key = 66;
					}

					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						prob = rand() % 50 + 1;
						e.e1->draw();
					}

					if (e.e1->judge == 1) // e1 is facing right
					{
						p1.ifHit(key, e.e1->state, e.e1->downPressed);
						if (e.e1->state == 1)
						{
							p1.moveRight(5);
						}
						else if (e.e1->state == 2)
						{
							p1.moveRight(15);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						p1.createBlood(p1.get_origin());
					}
				}

				if (double(prob) / 50 >= 0.4) // boss kick
				{
					if (flag_last || e.e1->kickPos != 0) {
						e.e1->kick();

						if (e.e1->downPressed == false)
							sound.PlayBackground(kick, true);
						// Kick
						key = 78;
					}


					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						prob = rand() % 50 + 1;
						e.e1->draw();
					}

					if (e.e1->judge == 1) // e1 is facing right
					{
						p1.ifHit(key, e.e1->state, e.e1->downPressed);
						if (e.e1->state == 1)
						{
							p1.moveRight(5);
						}

						if (e.e1->state == 2)
						{
							p1.moveRight(15);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						p1.createBlood(p1.get_origin());
					}
				}

				if (key == FSKEY_Z || key == FSKEY_X)
				{
					if (p1.judge == 0) // p1 is facing left
					{
						e.e1->ifHit(key, p1.state, p1.downPressed);
						if (p1.state == 1)
						{
							e.e1->moveLeft(60);
						}

						if (p1.state == 2)
						{
							e.e1->moveLeft(80);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						e.e1->createBlood(e.e1->get_origin());
					}
				}
			}
			else if (p1.get_origin().x - e.e1->get_origin().x >= -100 
			&& p1.get_origin().x - e.e1->get_origin().x <= 0 
			&& abs(p1.get_origin().y - e.e1->get_origin().y) < 100)// p1 is on the left
			{
				if (double(prob) / 50 < 0.4)// boss punch
				{
					// Punch
					if (flag_last || e.e1->punchPos != 0) {
						e.e1->punch();
						sound.PlayBackground(punch, true);
						// Kick
						key = 66;
					}

					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						prob = rand() % 50 + 1;
						e.e1->draw();
					}

					if (e.e1->judge == 0) // e1 is facing left
					{
						p1.ifHit(key, e.e1->state, e.e1->downPressed);
						if (e.e1->state == 1)
						{
							p1.moveLeft(5);
						}

						if (e.e1->state == 2)
						{
							p1.moveLeft(15);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						p1.createBlood(p1.get_origin());
					}
				}

				if (double(prob) / 50 >= 0.4) // boss kick
				{
					// Kick
					if (flag_last || e.e1->kickPos != 0) {
						e.e1->punch();
						if (e.e1->downPressed == false)
							sound.PlayBackground(kick, true);
						// Kick
						key = 78;
					}

					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						prob = rand() % 50 + 1;
						e.e1->draw();
					}

					if (e.e1->judge == 0) // e1 is facing left
					{
						p1.ifHit(key, e.e1->state, e.e1->downPressed);
						if (e.e1->state == 1)
						{
							p1.moveLeft(5);
						}

						if (e.e1->state == 2)
						{
							p1.moveLeft(15);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						p1.createBlood(p1.get_origin());
					}
				}

				if (key == FSKEY_Z || key == FSKEY_X)
				{
					if (p1.judge == 1) // p1 is facing right
					{
						e.e1->ifHit(key, p1.state, p1.downPressed);
						if (p1.state == 1)
						{
							e.e1->moveRight(60);
						}

						if (p1.state == 1)
						{
							e.e1->moveRight(80);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right", pve);

						e.e1->createBlood(e.e1->get_origin());
					}
				}
			}
			else
			{
				//
			}

			if (key == FSKEY_C || Cpressed)
			{
				Cpressed = true;
				int xMin = e.e1->get_origin().x - 0;
				int xMax = e.e1->get_origin().x + 0;
				int yMin = e.e1->get_origin().y - 10;
				int yMax = e.e1->get_origin().y + 90;
				if ((p1.get_origin_laser().x - xMin) >= 0 && (p1.get_origin_laser().x - xMax) <= 0
					&& (p1.get_origin_laser().y - yMin) >= 0 && (p1.get_origin_laser().y - yMax) <= 0)
				{
					p1.bullet_visible = false;
					e.e1->type_hit = 2;
					e.e1->createBlood(e.e1->get_origin());
					Cpressed = false;
				}
			}
			p1.handleLife();
			playerName = "left";
			p1.checkIfDie(terminate, playerName, pve);

			if (key == FSKEY_M || Mpressed)
			{
				Mpressed = true;
				int xMin = p1.get_origin().x - 0;
				int xMax = p1.get_origin().x + 0;
				int yMin = p1.get_origin().y - 10;
				int yMax = p1.get_origin().y + 90;
				if ((e.e1->get_origin_laser().x - xMin) >= 0 && (e.e1->get_origin_laser().x - xMax) <= 0
					&& (e.e1->get_origin_laser().y - yMin) >= 0 && (e.e1->get_origin_laser().y - yMax) <= 0)
				{
					e.e1->bullet_visible = false;
					p1.type_hit = 2;
					p1.createBlood(p1.get_origin());
					Mpressed = false;
				}
			}
			e.e1->handleLife();
			playerName = "right";
			e.e1->checkIfDie(terminate, playerName, pve);
		}
		else {
			e.e1 = new player((rand() % 100 + 500), 450, (rand() % 50 + 1),
				550.0, 50.0, 2, false, (rand() % 255), (rand() % 255), (rand() % 255), true);
			e.is_die = false;
		}

		// Check if Win
		p1.checkIfWin(terminate, num);

		FsSleep(20);
		FsSwapBuffers();

		flag++;
	}

	// =======================================Multiplayer===============================================

	while (!terminate && !pve)
	{

		FsPollDevice();
		key = FsInkey();

		if (FSKEY_ESC == key)
		{
			terminate = true;
		}

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
					p1.punch();
					sound.PlayBackground(punch, true);
				}

				else if (p1.state == 3) {
					p1.stab();
					sound.PlayBackground(knife, true);
				}
			}
		}

		if (key == FSKEY_X || p1.kickPos != 0)
		{

			if (p1.downPressed == FALSE)
			{
				p1.kick();
				sound.PlayBackground(kick, true);
			}
		}

		if (key == FSKEY_T)
			p1.showText();

		if (key == FSKEY_W || p1.InAir == TRUE)
		{
			p1.Jump(0.5);
		}

		if (key == FSKEY_C)
		{
			p1.bullet_init();
			p1.raise_arm();
			if (sound.IsPlaying(shoot) == 1)
			{
				sound.Stop(shoot);
			}

			if (p1.state == 2)
				sound.PlayBackground(shoot, true);

		}

		if (key == FSKEY_1) {            // differentiating states
			p1.state = 1;
		}

		if (key == FSKEY_2)
		{
			p1.state = 2;
		}

		if (key == FSKEY_3)
		{
			p1.state = 3;
		}

		if (p1.raisearm_x() != 0) {        // animation for moving arm up
			p1.raise_arm();
		}

		if (GetKeyState('S') < 0)
			p1.downPressed = TRUE;
		else
			p1.downPressed = FALSE;

		//1st to 2nd floor descent
		if (p1.get_origin().x < 50 && p1.get_origin().y < 175) {       // Moving down Yufan
			p1.set_origin(15, 450);
			p1.set_ystate(0);
		}
		/*if (p1.get_origin().x > 750 && p1.get_origin().y < 175) {
			p1.set_origin(775, 450);
			p1.set_ystate(0);
		}*/
		if (p2.get_origin().x < 50 && p2.get_origin().y < 175) {
			p2.set_origin(15, 450);
			p2.set_ystate(0);
		}
		/*if (p2.get_origin().x > 750 && p2.get_origin().y < 175) {
			p2.set_origin(775, 450);
			p2.set_ystate(0);                                           // Moing down Yufan
		}*/

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
					p2.punch();
					sound.PlayBackground(punch, true);
				}

				else if (p2.state == 3) {
					p2.stab();
					sound.PlayBackground(knife, true);
				}
			}
		}

		if (key == FSKEY_N || p2.kickPos != 0)
		{

			if (p2.downPressed == FALSE)
			{
				p2.kick();
				sound.PlayBackground(kick, true);
			}
		}

		if (key == FSKEY_Y)
			p2.showText();

		if (key == FSKEY_I || p2.InAir == TRUE)
		{
			p2.Jump(0.5);
		}

		if (key == FSKEY_M)
		{
			p2.bullet_init();
			p2.raise_arm();
			if (sound.IsPlaying(shoot) == 1)
			{
				sound.Stop(shoot);
			}

			if (p2.state == 2)
			{
				sound.PlayBackground(shoot, true);
			}
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
			glVertex2i(50 + size, 80 + size);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(50, 80 + size);
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

		if (p1.get_origin().x - p2.get_origin().x <= 100 && p1.get_origin().x - p2.get_origin().x >= 0 && abs(p1.get_origin().y - p2.get_origin().y) < 100)// p1 is on the right
		{
			if (key == FSKEY_B || key == FSKEY_N)
			{
				
				if (p2.judge == 1) // p2 is facing right
				{

					p1.ifHit(key, p2.state, p2.downPressed);
					
					if (key == FSKEY_B)
					{
						if (p2.state == 1)
						{
							p1.moveRight(5);
						}

						if (p2.state == 3)
						{
							p1.moveRight(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p1.createBlood(p1.get_origin());
					}
					else if (key == FSKEY_N && p2.downPressed == false)
					{
						if (p2.state == 1)
						{
							p1.moveRight(5);
						}

						if (p2.state == 3)
						{
							p1.moveRight(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p1.createBlood(p1.get_origin());
					}

				}
			}

			if (key == FSKEY_Z || key == FSKEY_X)
			{
				if (p1.judge == 0) // p1 is facing left
				{
					p2.ifHit(key, p1.state, p1.downPressed);
					if (key == FSKEY_Z)
					{
						if (p1.state == 1)
						{
							p2.moveLeft(5);
						}

						if (p1.state == 3)
						{
							p2.moveLeft(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p2.createBlood(p2.get_origin());
					}
					else if (key == FSKEY_X && p1.downPressed == false)
					{
						if (p1.state == 1)
						{
							p2.moveLeft(5);
						}

						if (p1.state == 3)
						{
							p2.moveLeft(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p2.createBlood(p2.get_origin());
					}

				}
			}
		}

		else if (p1.get_origin().x - p2.get_origin().x >= -100 && p1.get_origin().x - p2.get_origin().x <= 0 && abs(p1.get_origin().y - p2.get_origin().y) < 100)// p1 is on the left
		{
			if (key == FSKEY_B || key == FSKEY_N)
			{
				if (p2.judge == 0) // p2 is facing right
				{
					p1.ifHit(key, p2.state, p2.downPressed);
					if (key == FSKEY_B)
					{
						if (p2.state == 1)
						{
							p1.moveLeft(5);
						}
						else if (p2.state == 3)
						{
							p1.moveLeft(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p1.createBlood(p1.get_origin());
					}
					else if (key == FSKEY_N && p2.downPressed == false)
					{
						if (p2.state == 1)
						{
							p1.moveLeft(5);
						}
						else if (p2.state == 3)
						{
							p1.moveLeft(10);
						}

						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p1.createBlood(p1.get_origin());
					}
				}
			}

			if (key == FSKEY_Z || key == FSKEY_X)
			{
				if (p1.judge == 1) // p1 is facing left
				{
					p2.ifHit(key, p1.state, p1.downPressed);
		
					if (key == FSKEY_Z)
					{
						if (p1.state == 1)
						{
							p2.moveRight(5);
						}

						else if (p1.state == 3)
						{
							p2.moveRight(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p2.createBlood(p2.get_origin());
					}
					else if (key == FSKEY_X && p1.downPressed == false)
					{
						if (p1.state == 1)
						{
							p2.moveRight(5);
						}

						else if (p1.state == 3)
						{
							p2.moveRight(10);
						}
						p1.handleLife();
						p1.checkIfDie(terminate, "left", pve);
						p2.handleLife();
						p2.checkIfDie(terminate, "right", pve);
						p2.createBlood(p2.get_origin());
					}
				}

			}

		}
		else
		{
			//;
		}

		if (key == FSKEY_C || Cpressed)
		{
			Cpressed = true;
			int xMin = p2.get_origin().x - 5;
			int xMax = p2.get_origin().x + 5;
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
		p1.checkIfDie(terminate, playerName, pve);

		if (key == FSKEY_M || Mpressed)
		{
			Mpressed = true;
			int xMin = p1.get_origin().x - 5;
			int xMax = p1.get_origin().x + 5;
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
		p2.checkIfDie(terminate, playerName, pve);

		FsSleep(20);
		FsSwapBuffers();
	}
	return 0;
}