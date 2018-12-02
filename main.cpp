#include "player.h"
#include "menu.h"
#include "environment.h"

int main()
{
    bool terminateMenu = false, first = true, pve = true, secondInput = false;
    bool pveOrPvp = true, showButtons = false, ready = true;
    int key, pos = 0, loopCount = 0;
    Menu theMenu(800, 600);
    
    FsOpenWindow(16, 16, 1000, 600, 1);
    
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
    int flag = 0;
    bool flag_last = false;
    
    player p1(200, 450, 100, 50.0, 50.0, 1, true);
    player p2(600, 450, 100, 450.0, 50.0, 2, true);
    player e1(600, 450, 150, 400.0, 50.0, 2, true);
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
    
    //// MULTIPLAYER
    //while (!terminate)
    //{
    //    FsPollDevice();
    //    key = FsInkey();
    
    //    if (FSKEY_ESC ==key)
    //        terminate = true;
    
    //    /* Player I*/
    //
    //    if (GetKeyState('D') < 0)
    //    {
    //        p1.moveRight(10);
    //        p1.judge = 1;
    //    }
    //
    //    if (GetKeyState('A') < 0)
    //    {
    //        p1.moveLeft(10);
    //        p1.judge = 0;
    //    }
    //
    //
    //    if (key == FSKEY_Z || p1.punchPos != 0)
    //    {
    //        if (p1.state != 2)
    //        {
    //            if (p1.state == 1) {
    //                p1.punch(InAction1, InAction2);
    //                player.PlayBackground(punch);
    //            }
    //            else if (p1.state == 3) {
    //                p1.stab();
    //                player.PlayBackground(knife);
    //            }
    //        }
    //    }
    
    //    if (key == FSKEY_X || p1.kickPos != 0)
    //    {
    //        p1.kick();
    //        if(p1.downPressed==FALSE)
    //            player.PlayBackground(kick);
    
    //    }
    //    if (key == FSKEY_T)
    //        p1.showText();
    
    //    //if (key == FSKEY_B || BloodPos != 0)
    //    //{
    //    //    origin = p1.get_origin();
    //    //    createBlood(origin, BloodPos);
    //    //}
    
    //    if (key == FSKEY_W || p1.InAir==TRUE)
    //    {
    //        p1.Jump(0.5);
    //    }
    
    //    if (key == FSKEY_C)
    //    {
    //        p1.bullet_init();
    //        p1.raise_arm();
    //        if(player.IsPlaying(shoot)==1)
    //        {
    //            player.Stop(shoot);
    //            //cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
    //        }
    //        if(p1.state==2)
    //            player.PlayBackground(shoot);
    //    }
    //
    //    if (key == FSKEY_1) {            // differentiating states
    //        p1.state = 1;
    //    }
    
    //    if (key == FSKEY_2) {
    //        p1.state = 2;
    //    }
    
    //    if (key == FSKEY_3) {
    //        p1.state = 3;
    //    }
    
    //    if (p1.raisearm_x() != 0) {        // animation for moving arm up
    //        p1.raise_arm();
    //    }
    //
    //    if (GetKeyState('S') < 0)
    //        p1.downPressed = TRUE;
    //    else
    //        p1.downPressed = FALSE;
    
    //    /* Player II*/
    //    if (GetKeyState('L') < 0)
    //    {
    //        p2.moveRight(10);
    //        p2.judge = 1;
    //    }
    
    //    if (GetKeyState('J') < 0)
    //    {
    //        p2.moveLeft(10);
    //        p2.judge = 0;
    //    }
    
    //    if (key == FSKEY_B || p2.punchPos != 0)
    //    {
    //        if (p2.state != 2)
    //        {
    //            if (p2.state == 1) {
    //                p2.punch(InAction1, InAction2);
    //                player.PlayBackground(punch);
    //            }
    //            else if (p2.state == 3) {
    //                p2.stab();
    //                player.PlayBackground(knife);
    //            }
    //        }
    //    }
    
    //    if (key == FSKEY_N || p2.kickPos != 0)
    //    {
    //        p2.kick();
    //        if (p2.downPressed == FALSE)
    //            player.PlayBackground(kick);
    
    //    }
    //    if (key == FSKEY_Y)
    //        p2.showText();
    
    //    //if (key == FSKEY_B || BloodPos != 0)
    //    //{
    //    //    origin = p1.get_origin();
    //    //    createBlood(origin, BloodPos);
    //    //}
    
    //    if (key == FSKEY_I || p2.InAir == TRUE)
    //    {
    //        p2.Jump(0.5);
    //    }
    
    //    if (key == FSKEY_M)
    //    {
    //        p2.bullet_init();
    //        p2.raise_arm();
    //        if (player.IsPlaying(shoot) == 1)
    //        {
    //            player.Stop(shoot);
    //            //cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
    //        }
    //        if (p2.state == 2)
    //            player.PlayBackground(shoot);
    //    }
    
    //    if (key == FSKEY_7) {            // differentiating states
    //        p2.state = 1;
    //    }
    
    //    if (key == FSKEY_8) {
    //        p2.state = 2;
    //    }
    
    //    if (key == FSKEY_9) {
    //        p2.state = 3;
    //    }
    
    //    if (p2.raisearm_x() != 0) {        // animation for moving arm up
    //        p2.raise_arm();
    //    }
    
    //    if (GetKeyState('K') < 0)
    //        p2.downPressed = TRUE;
    //    else
    //        p2.downPressed = FALSE;
    
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    theEnvironment.draw();
    //    if (!p1.getIfDie()) {
    //        //            p1.stand();
    //        if (p1.state == 1)              // default standing position
    //            p1.draw();
    //        else if (p1.state == 2) {       // use shooter position
    //            p1.laser_position();
    //            p1.draw_laser();
    //            p1.laser_move();
    //        }
    //        else if (p1.state == 3) {       // use knife position
    //            p1.knife_position();
    //        }
    
    
    //        /* Life Part */
    //        p1.drawLife();
    
    //    }
    
    //    if (!p2.getIfDie()) {
    //        //            p1.stand();
    //        if (p2.state == 1)              // default standing position
    //            p2.draw();
    //        else if (p2.state == 2) {       // use shooter position
    //            p2.laser_position();
    //            p2.draw_laser();
    //            p2.laser_move();
    //        }
    //        else if (p2.state == 3) {       // use knife position
    //            p2.knife_position();
    //        }
    
    
    //        /* Life Part */
    //        p2.drawLife();
    
    
    //    }
    
    //    /*if (abs(p1.get_origin().x - p2.get_origin().x) <= 100)
    //    {
    //        p1.ifHit(key);
    //        p1.handleLife();
    //        playerName = "left";
    //        p1.checkIfDie(terminate, playerName);
    
    //        p2.ifHit(key);
    //        p2.handleLife();
    //        playerName = "right";
    //        p2.checkIfDie(terminate, playerName);
    //    }*/
    //    if (p1.get_origin().x - p2.get_origin().x <= 100 && p1.get_origin().x - p2.get_origin().x >= 0)// p1 is on the right
    //    {
    //        if (key == FSKEY_B || key == FSKEY_N)
    //        {
    //            if (p2.judge == 1) // p2 is facing right
    //            {
    //                p1.ifHit(key, p2.state);
    //                p1.moveRight(5);
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p1.createBlood(p1.get_origin());
    //            }
    //        }
    
    //        if (key == FSKEY_Z || key == FSKEY_X)
    //        {
    //            if (p1.judge == 0) // p1 is facing left
    //            {
    //                p2.ifHit(key, p1.state);
    //                p2.moveLeft(5);
    
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p2.createBlood(p2.get_origin());
    //            }
    //        }
    
    
    //    }
    //    else if (p1.get_origin().x - p2.get_origin().x >= -100 && p1.get_origin().x - p2.get_origin().x <= 0)// p1 is on the left
    //    {
    //        if (key == FSKEY_B || key == FSKEY_N)
    //        {
    //            if (p2.judge == 0) // p2 is facing right
    //            {
    //                p1.ifHit(key, p2.state);
    //                p1.moveLeft(5);
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p1.createBlood(p1.get_origin());
    //            }
    //        }
    
    //        if (key == FSKEY_Z || key == FSKEY_X)
    //        {
    //            if (p1.judge == 1) // p1 is facing left
    //            {
    //                p2.ifHit(key, p1.state);
    //                p2.moveRight(5);
    
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p2.createBlood(p2.get_origin());
    //            }
    //        }
    
    //    }
    //    else
    //    {
    //        //cout << abs(p1.get_origin_laser().y - p2.get_origin().y) << "\n";
    //        //cout << p2.type_hit << "\n";
    //
    //        if (key == FSKEY_C || Cpressed)
    //        {
    
    //            Cpressed = true;
    //            int xMin = p2.get_origin().x - 10;
    //            int xMax = p2.get_origin().x + 10;
    //            int yMin = p2.get_origin().y - 10;
    //            int yMax = p2.get_origin().y + 90;
    //            if ((p1.get_origin_laser().x - xMin) >= 0 && (p1.get_origin_laser().x - xMax) <= 0
    //                && (p1.get_origin_laser().y - yMin) >= 0 && (p1.get_origin_laser().y - yMax) <= 0)
    //            {
    //                p1.bullet_visible = false;
    //                p2.type_hit = 2;
    //                p2.createBlood(p2.get_origin());
    //                Cpressed = false;
    //            }
    //        }
    //        p1.handleLife();
    //        playerName = "left";
    //        p1.checkIfDie(terminate, playerName);
    
    //        if (key == FSKEY_M || Mpressed)
    //        {
    //            Mpressed = true;
    //            int xMin = p1.get_origin().x - 10;
    //            int xMax = p1.get_origin().x + 10;
    //            int yMin = p1.get_origin().y - 10;
    //            int yMax = p1.get_origin().y + 90;
    //            if ((p2.get_origin_laser().x - xMin) >= 0 && (p2.get_origin_laser().x - xMax) <= 0
    //                && (p2.get_origin_laser().y - yMin) >= 0 && (p2.get_origin_laser().y - yMax) <= 0)
    //            {
    //                p2.bullet_visible = false;
    //                p1.type_hit = 2;
    //                p1.createBlood(p1.get_origin());
    //                Mpressed = false;
    //            }
    //        }
    //        p2.handleLife();
    //        playerName = "right";
    //        p2.checkIfDie(terminate, playerName);
    //    }
    
    //    FsSleep(20);
    //    FsSwapBuffers();
    //}
    //// MULTIPLAYER
    //while (!terminate)
    //{
    //    FsPollDevice();
    //    key = FsInkey();
    
    //    if (FSKEY_ESC ==key)
    //        terminate = true;
    
    //    /* Player I*/
    //
    //    if (GetKeyState('D') < 0)
    //    {
    //        p1.moveRight(10);
    //        p1.judge = 1;
    //    }
    //
    //    if (GetKeyState('A') < 0)
    //    {
    //        p1.moveLeft(10);
    //        p1.judge = 0;
    //    }
    //
    //
    //    if (key == FSKEY_Z || p1.punchPos != 0)
    //    {
    //        if (p1.state != 2)
    //        {
    //            if (p1.state == 1) {
    //                p1.punch(InAction1, InAction2);
    //                player.PlayBackground(punch);
    //            }
    //            else if (p1.state == 3) {
    //                p1.stab();
    //                player.PlayBackground(knife);
    //            }
    //        }
    //    }
    
    //    if (key == FSKEY_X || p1.kickPos != 0)
    //    {
    //        p1.kick();
    //        if(p1.downPressed==FALSE)
    //            player.PlayBackground(kick);
    
    //    }
    //    if (key == FSKEY_T)
    //        p1.showText();
    
    //    //if (key == FSKEY_B || BloodPos != 0)
    //    //{
    //    //    origin = p1.get_origin();
    //    //    createBlood(origin, BloodPos);
    //    //}
    
    //    if (key == FSKEY_W || p1.InAir==TRUE)
    //    {
    //        p1.Jump(0.5);
    //    }
    
    //    if (key == FSKEY_C)
    //    {
    //        p1.bullet_init();
    //        p1.raise_arm();
    //        if(player.IsPlaying(shoot)==1)
    //        {
    //            player.Stop(shoot);
    //            //cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
    //        }
    //        if(p1.state==2)
    //            player.PlayBackground(shoot);
    //    }
    //
    //    if (key == FSKEY_1) {            // differentiating states
    //        p1.state = 1;
    //    }
    
    //    if (key == FSKEY_2) {
    //        p1.state = 2;
    //    }
    
    //    if (key == FSKEY_3) {
    //        p1.state = 3;
    //    }
    
    //    if (p1.raisearm_x() != 0) {        // animation for moving arm up
    //        p1.raise_arm();
    //    }
    //
    //    if (GetKeyState('S') < 0)
    //        p1.downPressed = TRUE;
    //    else
    //        p1.downPressed = FALSE;
    
    //    /* Player II*/
    //    if (GetKeyState('L') < 0)
    //    {
    //        p2.moveRight(10);
    //        p2.judge = 1;
    //    }
    
    //    if (GetKeyState('J') < 0)
    //    {
    //        p2.moveLeft(10);
    //        p2.judge = 0;
    //    }
    
    //    if (key == FSKEY_B || p2.punchPos != 0)
    //    {
    //        if (p2.state != 2)
    //        {
    //            if (p2.state == 1) {
    //                p2.punch(InAction1, InAction2);
    //                player.PlayBackground(punch);
    //            }
    //            else if (p2.state == 3) {
    //                p2.stab();
    //                player.PlayBackground(knife);
    //            }
    //        }
    //    }
    
    //    if (key == FSKEY_N || p2.kickPos != 0)
    //    {
    //        p2.kick();
    //        if (p2.downPressed == FALSE)
    //            player.PlayBackground(kick);
    
    //    }
    //    if (key == FSKEY_Y)
    //        p2.showText();
    
    //    //if (key == FSKEY_B || BloodPos != 0)
    //    //{
    //    //    origin = p1.get_origin();
    //    //    createBlood(origin, BloodPos);
    //    //}
    
    //    if (key == FSKEY_I || p2.InAir == TRUE)
    //    {
    //        p2.Jump(0.5);
    //    }
    
    //    if (key == FSKEY_M)
    //    {
    //        p2.bullet_init();
    //        p2.raise_arm();
    //        if (player.IsPlaying(shoot) == 1)
    //        {
    //            player.Stop(shoot);
    //            //cout << "yyyyyyyyyyyyyyyyyyyyyyy" << endl;
    //        }
    //        if (p2.state == 2)
    //            player.PlayBackground(shoot);
    //    }
    
    //    if (key == FSKEY_7) {            // differentiating states
    //        p2.state = 1;
    //    }
    
    //    if (key == FSKEY_8) {
    //        p2.state = 2;
    //    }
    
    //    if (key == FSKEY_9) {
    //        p2.state = 3;
    //    }
    
    //    if (p2.raisearm_x() != 0) {        // animation for moving arm up
    //        p2.raise_arm();
    //    }
    
    //    if (GetKeyState('K') < 0)
    //        p2.downPressed = TRUE;
    //    else
    //        p2.downPressed = FALSE;
    
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    theEnvironment.draw();
    //    if (!p1.getIfDie()) {
    //        //            p1.stand();
    //        if (p1.state == 1)              // default standing position
    //            p1.draw();
    //        else if (p1.state == 2) {       // use shooter position
    //            p1.laser_position();
    //            p1.draw_laser();
    //            p1.laser_move();
    //        }
    //        else if (p1.state == 3) {       // use knife position
    //            p1.knife_position();
    //        }
    
    
    //        /* Life Part */
    //        p1.drawLife();
    
    //    }
    
    //    if (!p2.getIfDie()) {
    //        //            p1.stand();
    //        if (p2.state == 1)              // default standing position
    //            p2.draw();
    //        else if (p2.state == 2) {       // use shooter position
    //            p2.laser_position();
    //            p2.draw_laser();
    //            p2.laser_move();
    //        }
    //        else if (p2.state == 3) {       // use knife position
    //            p2.knife_position();
    //        }
    
    
    //        /* Life Part */
    //        p2.drawLife();
    
    
    //    }
    
    //    /*if (abs(p1.get_origin().x - p2.get_origin().x) <= 100)
    //    {
    //        p1.ifHit(key);
    //        p1.handleLife();
    //        playerName = "left";
    //        p1.checkIfDie(terminate, playerName);
    
    //        p2.ifHit(key);
    //        p2.handleLife();
    //        playerName = "right";
    //        p2.checkIfDie(terminate, playerName);
    //    }*/
    //    if (p1.get_origin().x - p2.get_origin().x <= 100 && p1.get_origin().x - p2.get_origin().x >= 0)// p1 is on the right
    //    {
    //        if (key == FSKEY_B || key == FSKEY_N)
    //        {
    //            if (p2.judge == 1) // p2 is facing right
    //            {
    //                p1.ifHit(key, p2.state);
    //                p1.moveRight(5);
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p1.createBlood(p1.get_origin());
    //            }
    //        }
    
    //        if (key == FSKEY_Z || key == FSKEY_X)
    //        {
    //            if (p1.judge == 0) // p1 is facing left
    //            {
    //                p2.ifHit(key, p1.state);
    //                p2.moveLeft(5);
    
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p2.createBlood(p2.get_origin());
    //            }
    //        }
    
    
    //    }
    //    else if (p1.get_origin().x - p2.get_origin().x >= -100 && p1.get_origin().x - p2.get_origin().x <= 0)// p1 is on the left
    //    {
    //        if (key == FSKEY_B || key == FSKEY_N)
    //        {
    //            if (p2.judge == 0) // p2 is facing right
    //            {
    //                p1.ifHit(key, p2.state);
    //                p1.moveLeft(5);
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p1.createBlood(p1.get_origin());
    //            }
    //        }
    
    //        if (key == FSKEY_Z || key == FSKEY_X)
    //        {
    //            if (p1.judge == 1) // p1 is facing left
    //            {
    //                p2.ifHit(key, p1.state);
    //                p2.moveRight(5);
    
    
    //                p1.handleLife();
    //                p1.checkIfDie(terminate, "left");
    
    //                p2.handleLife();
    //                p2.checkIfDie(terminate, "right");
    
    //                p2.createBlood(p2.get_origin());
    //            }
    //        }
    
    //    }
    //    else
    //    {
    //        //cout << abs(p1.get_origin_laser().y - p2.get_origin().y) << "\n";
    //        //cout << p2.type_hit << "\n";
    //
    //        if (key == FSKEY_C || Cpressed)
    //        {
    
    //            Cpressed = true;
    //            int xMin = p2.get_origin().x - 10;
    //            int xMax = p2.get_origin().x + 10;
    //            int yMin = p2.get_origin().y - 10;
    //            int yMax = p2.get_origin().y + 90;
    //            if ((p1.get_origin_laser().x - xMin) >= 0 && (p1.get_origin_laser().x - xMax) <= 0
    //                && (p1.get_origin_laser().y - yMin) >= 0 && (p1.get_origin_laser().y - yMax) <= 0)
    //            {
    //                p1.bullet_visible = false;
    //                p2.type_hit = 2;
    //                p2.createBlood(p2.get_origin());
    //                Cpressed = false;
    //            }
    //        }
    //        p1.handleLife();
    //        playerName = "left";
    //        p1.checkIfDie(terminate, playerName);
    
    //        if (key == FSKEY_M || Mpressed)
    //        {
    //            Mpressed = true;
    //            int xMin = p1.get_origin().x - 10;
    //            int xMax = p1.get_origin().x + 10;
    //            int yMin = p1.get_origin().y - 10;
    //            int yMax = p1.get_origin().y + 90;
    //            if ((p2.get_origin_laser().x - xMin) >= 0 && (p2.get_origin_laser().x - xMax) <= 0
    //                && (p2.get_origin_laser().y - yMin) >= 0 && (p2.get_origin_laser().y - yMax) <= 0)
    //            {
    //                p2.bullet_visible = false;
    //                p1.type_hit = 2;
    //                p1.createBlood(p1.get_origin());
    //                Mpressed = false;
    //            }
    //        }
    //        p2.handleLife();
    //        playerName = "right";
    //        p2.checkIfDie(terminate, playerName);
    //    }
    
    //    FsSleep(20);
    //    FsSwapBuffers();
    //}
    
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
                    p1.punch(InAction1, InAction2);
                    player.PlayBackground(punch);
                }
                else if (p1.state == 3) {
                    p1.stab();
                    player.PlayBackground(knife);
                }
            }
        }
        
        if (key == FSKEY_X || p1.kickPos != 0)
        {
            p1.kick();
            if (p1.downPressed == false)
                player.PlayBackground(kick);
            
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
            if (player.IsPlaying(shoot) == 1)
            {
                player.Stop(shoot);
            }
            if (p1.state == 2)
                player.PlayBackground(shoot);
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
        
        /* Enemy*/
        //if (GetKeyState('L') < 0)
        //{
        //    p2.moveRight(10);
        //    p2.judge = 1;
        //}
        
        //if (GetKeyState('J') < 0)
        //{
        //    p2.moveLeft(10);
        //    p2.judge = 0;
        //}
        
        //if (key == FSKEY_B || p2.punchPos != 0)
        //{
        //    if (p2.state != 2)
        //    {
        //        if (p2.state == 1) {
        //            p2.punch(InAction1, InAction2);
        //            player.PlayBackground(punch);
        //        }
        //        else if (p2.state == 3) {
        //            p2.stab();
        //            player.PlayBackground(knife);
        //        }
        //    }
        //}
        
        //if (key == FSKEY_N || p2.kickPos != 0)
        //{
        //    p2.kick();
        //    if (p2.downPressed == FALSE)
        //        player.PlayBackground(kick);
        
        //}
        //if (key == FSKEY_Y)
        //    p2.showText();
        
        //if (key == FSKEY_I || p2.InAir == TRUE)
        //{
        //    p2.Jump(0.5);
        //}
        
        //if (key == FSKEY_M)
        //{
        //    p2.bullet_init();
        //    p2.raise_arm();
        //    if (player.IsPlaying(shoot) == 1)
        //    {
        //        player.Stop(shoot);
        //    }
        //    if (p2.state == 2)
        //        player.PlayBackground(shoot);
        //}
        
        //if (key == FSKEY_7) {            // differentiating states
        //    p2.state = 1;
        //}
        
        //if (key == FSKEY_8) {
        //    p2.state = 2;
        //}
        
        //if (key == FSKEY_9) {
        //    p2.state = 3;
        //}
        
        if (p2.raisearm_x() != 0) {        // animation for moving arm up
            p2.raise_arm();
        }
        
        //if (GetKeyState('K') < 0)
        //    p2.downPressed = TRUE;
        //else
        //    p2.downPressed = FALSE;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        theEnvironment.draw();
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
        
        if (!e1.getIfDie()) {
            //            p1.stand();
            if (e1.state == 1)              // default standing position
                e1.draw();
            else if (e1.state == 2) {       // use shooter position
                e1.laser_position();
                e1.draw_laser();
                e1.laser_move();
            }
            else if (e1.state == 3) {       // use knife position
                e1.knife_position();
            }
            /* Life Part */
            e1.drawLife();
        }
        
        /*
         1. boss cannot shoot
         2. boss will always follow you until one is dead
         3. boss will use gun when its hp drops below 20%
         
         */
        
        // Boss following control
        if (p1.get_origin().x - e1.get_origin().x > 100) // p1 is on the right, boss will follow and move to the right
        {
            e1.moveRight(10);
            e1.judge = 1;
        }
        
        if (p1.get_origin().x - e1.get_origin().x < -100) // p1 is on the left, boss will follow and move to the left
        {
            e1.moveLeft(10);
            e1.judge = 0;
        }
        
        // Boss fighting control
        
        int prob = rand() % 50 + 1;
        cout << "Prob: " << prob << endl;
        cout << "Flag: " << flag << endl;
        
        if (80 <= flag)
            flag_last = true;
        
        if (p1.get_origin().x - e1.get_origin().x <= 100 && p1.get_origin().x - e1.get_origin().x >= 0)// p1 is on the right
        {
            if (double(prob) / 50 < 0.4 && flag_last) // boss punch
            {
                if (flag >= 100){
                    flag = 0;
                    flag_last = false;
                    e1.draw();
                }
                
                // Punch
                e1.punch(InAction1, InAction2);
                player.PlayBackground(punch);
                
                // Kick
                key = 66;
                
                if (e1.judge == 1) // e1 is facing right
                {
                    p1.ifHit(key, p2.state);
                    p1.moveRight(5);
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    p1.createBlood(p1.get_origin());
                }
            }
            
            if (double(prob) / 50 >= 0.4 && flag_last) // boss kick
            {
                if (flag >= 100){
                    flag = 0;
                    flag_last = false;
                    e1.draw();
                }
                
                // Kick
                e1.kick();
                if (e1.downPressed == false)
                    player.PlayBackground(kick);
                
                // Kick
                key = 78;
                
                if (e1.judge == 1) // e1 is facing right
                {
                    p1.ifHit(key, p2.state);
                    p1.moveRight(5);
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    p1.createBlood(p1.get_origin());
                }
            }
            
            if (key == FSKEY_Z || key == FSKEY_X)
            {
                if (p1.judge == 0) // p1 is facing left
                {
                    e1.ifHit(key, p1.state);
                    e1.moveLeft(5);
                    
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    e1.createBlood(e1.get_origin());
                }
            }
        }
        else if (p1.get_origin().x - e1.get_origin().x >= -100 && p1.get_origin().x - e1.get_origin().x <= 0)// p1 is on the left
        {
            
            if (double(prob) / 50 < 0.4 && flag_last) // boss punch
            {
                if (flag >= 100){
                    flag = 0;
                    flag_last = false;
                    e1.draw();
                }
                
                // Punch
                e1.punch(InAction1, InAction2);
                player.PlayBackground(punch);
                
                // Kick
                key = 66;
                
                if (e1.judge == 0) // e1 is facing left
                {
                    p1.ifHit(key, p2.state);
                    p1.moveLeft(5);
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    p1.createBlood(p1.get_origin());
                }
            }
            
            if (double(prob) / 50 >= 0.4 && flag_last) // boss kick
            {
                if (flag >= 100){
                    flag = 0;
                    flag_last = false;
                    e1.draw();
                }
                
                // Kick
                e1.kick();
                if (e1.downPressed == false)
                    player.PlayBackground(kick);
                
                // Kick
                key = 78;
                
                if (e1.judge == 0) // e1 is facing left
                {
                    p1.ifHit(key, p2.state);
                    p1.moveLeft(5);
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    p1.createBlood(p1.get_origin());
                }
            }
            
            if (key == FSKEY_Z || key == FSKEY_X)
            {
                if (p1.judge == 1) // p1 is facing right
                {
                    e1.ifHit(key, p1.state);
                    e1.moveRight(5);
                    
                    p1.handleLife();
                    p1.checkIfDie(terminate, "left");
                    
                    e1.handleLife();
                    e1.checkIfDie(terminate, "right");
                    
                    e1.createBlood(e1.get_origin());
                }
            }
            
        }
        else
        {
            
            if (key == FSKEY_C || Cpressed)
            {
                
                Cpressed = true;
                int xMin = e1.get_origin().x - 10;
                int xMax = e1.get_origin().x + 10;
                int yMin = e1.get_origin().y - 10;
                int yMax = e1.get_origin().y + 90;
                if ((p1.get_origin_laser().x - xMin) >= 0 && (p1.get_origin_laser().x - xMax) <= 0
                    && (p1.get_origin_laser().y - yMin) >= 0 && (p1.get_origin_laser().y - yMax) <= 0)
                {
                    p1.bullet_visible = false;
                    e1.type_hit = 2;
                    e1.createBlood(e1.get_origin());
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
                if ((e1.get_origin_laser().x - xMin) >= 0 && (e1.get_origin_laser().x - xMax) <= 0
                    && (e1.get_origin_laser().y - yMin) >= 0 && (e1.get_origin_laser().y - yMax) <= 0)
                {
                    e1.bullet_visible = false;
                    p1.type_hit = 2;
                    p1.createBlood(p1.get_origin());
                    Mpressed = false;
                }
            }
            e1.handleLife();
            playerName = "right";
            e1.checkIfDie(terminate, playerName);
        }
        
        FsSleep(20);
        FsSwapBuffers();
        
        flag++;
    }
    return 0;
}

