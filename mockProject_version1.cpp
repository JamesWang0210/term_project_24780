#include "player.h"
#include "menu.h"

int main()
{
	bool terminateMenu = false, first = true, pve = true, secondInput = false;
	bool pveOrPvp = true, showButtons = false, ready = true;
	int key, pos = 0, loopCount = 0;
	Menu theMenu(800, 600);
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
	return 0;
}

