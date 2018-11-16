#include <iostream>
#include "fssimplewindow.h"
#include "environment.h"

int main()
{
	bool terminate = false;

	FsOpenWindow(16, 16, 800, 600, 1);
	Environment theEnvironment;
	while (!terminate) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		FsPollDevice();

		theEnvironment.draw();

		FsSwapBuffers();
		FsSleep(25);
	}

	return 0;
}