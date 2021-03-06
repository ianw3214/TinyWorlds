#include <iostream>
#include <ctime>
#include <cstdlib>

#include "engine.hh"
#include "level1.hh"
#include "level2.hh"
#include "last.hh"
#include "mainMenu.hh"

int main(int argc, char* argv[]) {

	// initialize seed for random number
	srand(time(NULL));

	engine * gameEngine = new engine();
	// RUN THE GAME IF ENGINE SUCCESSFULLY INITIALIZES
	if (gameEngine->init()) {
		// level1 * test1 = new level1();
		// level2 * test1 = new level2();
		mainMenu * test1 = new mainMenu();
		// last * test1 = new last();
		gameEngine->setState(test1);

		// game loop
		while (gameEngine->isRunning()) {
			gameEngine->handleEvents();
			gameEngine->update();
			gameEngine->render();
		}

		gameEngine->close();
	}

	return 0;

}