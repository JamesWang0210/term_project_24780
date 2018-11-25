#include "player_1.h"

int main()
{
    bool terminate = false;
    int key;
    bool InAir = false;
    bool downPressed = false;
    int type_hit = -1;
    Coordinate origin;
    player p1(400, 450, 100, 50.0, 50.0, 1, true);
    int punchPos = 0;
    int kickpos = 0;
    FsOpenWindow(16, 16, 800, 600, 1);
    int BloodPos = 0;
    float v = 50;
    int state = 1;
    
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
        
        if (FSKEY_ESC ==key)
            terminate = true;
        
        if (FsGetKeyState('D') < 0)
            p1.moveRight();
        
        if (FsGetKeyState('A') < 0)
            p1.moveLeft();
        
        if (key == FSKEY_Z || punchPos != 0)
        {
            if (state != 2)
            {
                p1.punch(punchPos);
                if (state == 1)
                    player.PlayBackground(punch);
                else
                    player.PlayBackground(knife);
            }
        }
        
        if (key == FSKEY_X || kickpos != 0)
        {
            p1.kick(kickpos);
            if(downPressed==false)
                player.PlayBackground(kick);
            
        }
        
        if (key == FSKEY_T)
            p1.showText();
        
        if (key == FSKEY_B || BloodPos != 0)
        {
            origin = p1.get_origin();
            createBlood(origin, BloodPos);
            
        }
        
        if (key == FSKEY_W || InAir==true)
        {
            p1.Jump(0.5,v,InAir);
        }
        
        if (key == FSKEY_C && state ==2)
        {
            p1.start_a_bullet();
            //p1.draw_lasers();
            p1.raise_arm();
            
            if(player.IsPlaying(shoot)==1)
            {
                player.Stop(shoot);
                cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
            }
            if(state==2)
                player.PlayBackground(shoot);
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
        
        if (FsGetKeyState('S') < 0)
            downPressed = true;
        else
            downPressed = false;
        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (!p1.getIfDie()) {
            //            p1.stand();
            if (state == 1)              // default standing position
                p1.draw(downPressed,InAir);
            else if (state == 2) {       // use shooter position
                p1.laser_position(downPressed, InAir);
                p1.draw_lasers();        //
                p1.laser_move();       //
                p1.process_lasers();
            }
            else if (state == 3) {       // use knife position
                p1.knife_position(downPressed, InAir);
            }
            /* Life Part */
            p1.drawLife();
            p1.ifHit(key, type_hit, state);
            p1.handleLife(type_hit);
            p1.checkIfDie(terminate);
        }
        
        FsSleep(20);
        FsSwapBuffers();
    }
}
