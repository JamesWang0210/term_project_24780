#include "player.h"

int main()
{
    bool terminate = false;
    int key;
    
    int type_hit = -1;
    
    player p1(100, 50.0, 50.0, 1, true);
    int punchPos=0;
    int kickpos = 0;
	int state = 1;


    FsOpenWindow(16, 16, 800, 600, 1);
    
    while (!terminate)
    {
        FsPollDevice();
        key = FsInkey();
        
        switch (key)
        {
            case(FSKEY_ESC):
                terminate = true;
                break;
            case(FSKEY_RIGHT):
                p1.moveRight();
                break;
            case(FSKEY_LEFT):
                p1.moveLeft();
                break;
            case(FSKEY_Z):
                p1.punch(punchPos);
                break;
            case(FSKEY_X):
                p1.kick(kickpos);
                break;

			case(FSKEY_C):
				p1.bullet_init();
				p1.raise_arm();
				break;

			case(FSKEY_1):
				state = 1;
				break;

			case(FSKEY_2):
				state = 2;
				break;
			case(FSKEY_3):
				state = 3;
				break;

        }
        if (punchPos != 0)
        {
            p1.punch(punchPos);
        }
        if (kickpos != 0)
        {
            p1.kick(kickpos);
        }

		if (p1.raisearm_x() != 0) {
			p1.raise_arm();
		}


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(!p1.getIfDie()){
            //            p1.stand();



			if (state == 1)
				p1.draw();
			else if (state == 2) {
				p1.laser_position();        // use knife position
				p1.draw_laser();
				p1.laser_move();
			}
			else if (state == 3) {
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

