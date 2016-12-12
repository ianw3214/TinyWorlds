#include <iostream>

#include "engine.hh"
#include "level1.hh"

int main(int argc, char* argv[]) {

	engine * gameEngine = new engine();
	// RUN THE GAME IF ENGINE SUCCESSFULLY INITIALIZES
	if (gameEngine->init()) {
		level1 * test1 = new level1();
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