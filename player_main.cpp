#include "player.h"

int main()
{
	srand(time(NULL));
    bool terminate = false;
    int key;
	bool left = true, right = true;
    int type_hit = -1;
	int enemy_type_hit = -1;
    
    player p1(400, 450, 100, 50.0, 50.0, 1, true);
    int punchPos_1 = 0;
    int kickpos_1 = 0;
	int kickpos_3 = 0;
    
    player e1(600, 450, 50, 550.0, 50.0, 2, false);
    int punchPos_2 = 0;
    int kickpos_2 = 0;
    
    FsOpenWindow(16, 16, 800, 600, 1);
    
    // Check how many stickman in the screen
    int num_player = 1;
    int num_enemy = 10;
    
    int num_total = num_player + num_enemy;
    // End
    
    while (!terminate)
    {
        FsPollDevice();
        key = FsInkey();
        
        switch (key)
        {
            case(FSKEY_ESC):
                terminate = true;
                break;
            // Key for player
            case(FSKEY_A):
				p1.moveLeft();
                break;
            case(FSKEY_D):
                p1.moveRight();
                break;
            case(FSKEY_Z):
                p1.punch(punchPos_1);
                break;
            case(FSKEY_X):
                p1.kick(kickpos_1);
                break;
			case(FSKEY_C):
				p1.bullet_init();
				p1.raise_arm();
				cout << "ok!" << endl;
				break;
        }
		if ((e1.getOrigin().x - p1.getOrigin().x) > 100)
		{
			e1.moveLeft();
		}
		if ((e1.getOrigin().x - p1.getOrigin().x) < -100)
		{
			e1.moveRight();
		}
        if (punchPos_1 != 0)
        {
            p1.punch(punchPos_1);
        }
        
        if (kickpos_1 != 0)
        {
            p1.kick(kickpos_1);
        }
        
        if (punchPos_2 != 0)
        {
            e1.punch(punchPos_2);
        }
        
        if (kickpos_2 != 0)
        {
            e1.kick(kickpos_2);
        }

		if (p1.raisearm.x != 0) {
			p1.raise_arm();
		}

        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (abs(p1.getOrigin().x - e1.getOrigin().x) <= 100){
            p1.ifHit(key, enemy_type_hit);
            p1.handleLife(enemy_type_hit);
            p1.checkIfDie(terminate);
			int random = rand() % 1000 + 1;
			if (random <= 300)
			{
				enemy_type_hit = 0;
				e1.punch(punchPos_2);
			}
			else
			{
				enemy_type_hit = 1;
				e1.kick(kickpos_2);
			}
            e1.handleLife(type_hit);
            e1.checkIfDie(terminate);
        }
        
        if(!p1.getIfDie()){
            //            p1.stand();
            //p1.draw();


			p1.laser_position();        // testing: use knife position
			p1.draw_laser();
			p1.laser_move();
            
            /* Life Part */
            p1.drawLife();
//            p1.ifHit(key, type_hit);
//            p1.handleLife(type_hit);
//            p1.checkIfDie(terminate);
        }
        
        if(!e1.getIfDie()){
            //            p1.stand();
            e1.draw();
            
            /* Life Part */
            e1.drawLife();
//            e1.ifHit(key, type_hit);
//            e1.handleLife(type_hit);
//            e1.checkIfDie(terminate);
        }

        FsSleep(20);
        FsSwapBuffers();
    }
}

