#include "player.h"
#include "menu.h"
#include "environment.h"

int main()
{
	bool terminateMenu = false, first = true, pve = true, secondInput = false;
	bool pveOrPvp = true, showButtons = false, ready = true;
	int key, pos = 0, loopCount = 0;
	Menu theMenu(800, 600);

	int num = 0;

	FsOpenWindow(16, 16, 800, 600, 1);

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
	/*bool InAction1 = false;
	bool InAction2 = false;*/
	bool Cpressed = false;
	bool Mpressed = false;
	//Coordinate origin;
	//int BloodPos = 0;
	int flag = 0;
	bool flag_last = false;

	player p1(200, 450, 100, 50.0, 50.0, 1, true);
	player p2(600, 450, 100, 450.0, 50.0, 2, false);
	enemy e;
	//    player *e1 = new player(600, 450, 10, 600.0, 50.0, 2, false);
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

	//    if (e.e1->getIfDie())
	//    {
	//        if (e.e1 != nullptr){
	//            delete[] e.e1;
	//            e.e1 = nullptr;
	//            e.is_die = true;
	//        }
	//    }
	//
	//    if (e.e1->getIfDie())
	//    {
	//        e.e1 = new player (rand() % 100 + 500, 450, 50, 450.0, 50.0, 2, false);
	//        e.is_die = false;
	//    }


		// SINGLEPLAYER
	while (!terminate)
	{
		FsPollDevice();
		key = FsInkey();

		if (FSKEY_ESC == key)
			terminate = true;

		/* Player I*/

		if (key == FSKEY_D)
		{
			p1.moveRight(10);
			p1.judge = 1;
		}

		if (key == FSKEY_A)
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
			p1.kick();
			if (p1.downPressed == false)
				sound.PlayBackground(kick, true);

		}
		if (key == FSKEY_T)
			p1.showText();

		if (key == FSKEY_W || p1.InAir == true)
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

		if (key == FSKEY_2) {
			p1.state = 2;
		}

		if (key == FSKEY_3) {
			p1.state = 3;
		}

		if (p1.raisearm_x() != 0) {        // animation for moving arm up
			p1.raise_arm();
		}

		if (key == FSKEY_S)
			p1.downPressed = true;
		else
			p1.downPressed = false;

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
				e.e1->moveRight(10);
				e.e1->judge = 1;
			}

			if (p1.get_origin().x - e.e1->get_origin().x < -100) // p1 is on the left, boss will follow and move to the left
			{
				e.e1->moveLeft(10);
				e.e1->judge = 0;
			}

			// Boss fighting control

			int prob = rand() % 50 + 1;
			cout << "Prob: " << prob << endl;
			cout << "Flag: " << flag << endl;

			if (80 <= flag)
				flag_last = true;

			if (p1.get_origin().x - e.e1->get_origin().x <= 100 && p1.get_origin().x - e.e1->get_origin().x >= 0)// p1 is on the right
			{
				if (double(prob) / 50 < 0.4 && flag_last) // boss punch
				{
					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						e.e1->draw();
					}

					// Punch
					e.e1->punch();
					sound.PlayBackground(punch, true);

					// Kick
					key = 66;

					if (e.e1->judge == 1) // e1 is facing right
					{
						p1.ifHit(key, p2.state);
						p1.moveRight(5);

						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						p1.createBlood(p1.get_origin());
					}
				}

				if (double(prob) / 50 >= 0.4 && flag_last) // boss kick
				{
					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						e.e1->draw();
					}

					// Kick
					e.e1->kick();
					if (e.e1->downPressed == false)
						sound.PlayBackground(kick, true);

					// Kick
					key = 78;

					if (e.e1->judge == 1) // e1 is facing right
					{
						p1.ifHit(key, p2.state);
						p1.moveRight(5);

						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						p1.createBlood(p1.get_origin());
					}
				}

				if (key == FSKEY_Z || key == FSKEY_X)
				{
					if (p1.judge == 0) // p1 is facing left
					{
						e.e1->ifHit(key, p1.state);
						e.e1->moveLeft(5);


						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						e.e1->createBlood(e.e1->get_origin());
					}
				}
			}
			else if (p1.get_origin().x - e.e1->get_origin().x >= -100 && p1.get_origin().x - e.e1->get_origin().x <= 0)// p1 is on the left
			{

				if (double(prob) / 50 < 0.4 && flag_last) // boss punch
				{
					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						e.e1->draw();
					}

					// Punch
					e.e1->punch();
					sound.PlayBackground(punch, true);

					// Kick
					key = 66;

					if (e.e1->judge == 0) // e1 is facing left
					{
						p1.ifHit(key, p2.state);
						p1.moveLeft(5);

						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						p1.createBlood(p1.get_origin());
					}
				}

				if (double(prob) / 50 >= 0.4 && flag_last) // boss kick
				{
					if (flag >= 100) {
						flag = 0;
						flag_last = false;
						e.e1->draw();
					}

					// Kick
					e.e1->kick();
					if (e.e1->downPressed == false)
						sound.PlayBackground(kick, true);

					// Kick
					key = 78;

					if (e.e1->judge == 0) // e1 is facing left
					{
						p1.ifHit(key, p2.state);
						p1.moveLeft(5);

						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						p1.createBlood(p1.get_origin());
					}
				}

				if (key == FSKEY_Z || key == FSKEY_X)
				{
					if (p1.judge == 1) // p1 is facing right
					{
						e.e1->ifHit(key, p1.state);
						e.e1->moveRight(5);

						p1.handleLife();
						p1.checkIfDie(terminate, "left");

						e.e1->handleLife();
						e.e1->checkIfDie(terminate, "right");

						e.e1->createBlood(e.e1->get_origin());
					}
				}
			}
			else
			{

				if (key == FSKEY_C || Cpressed)
				{

					Cpressed = true;
					int xMin = e.e1->get_origin().x - 10;
					int xMax = e.e1->get_origin().x + 10;
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
				p1.checkIfDie(terminate, playerName);

				if (key == FSKEY_M || Mpressed)
				{
					Mpressed = true;
					int xMin = p1.get_origin().x - 10;
					int xMax = p1.get_origin().x + 10;
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
				e.e1->checkIfDie(terminate, playerName);
			}
		}
		else {
			e.e1 = new player(rand() % 100 + 500, 450, 50, 450.0, 50.0, 2, false);
			e.is_die = false;
		}

		// Check if Win
		p1.checkIfWin(terminate, num);

		/*
		 1. boss cannot shoot
		 2. boss will always follow you until one is dead
		 3. boss will use gun when its hp drops below 20%
		 */

		FsSleep(20);
		FsSwapBuffers();

		flag++;
	}

	return 0;
}


//if(num == 1){
//    e.e1 = new player (rand() % 100 + 500, 450, 50, 450.0, 50.0, 2, false);
//    e.is_die = false;
//    num = 2;
//}