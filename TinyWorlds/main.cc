#include <iostream>

#include "engine.hh"
#include "playState.hh"

int main(int argc, char* argv[]) {

	engine * gameEngine = new engine();
	// RUN THE GAME IF ENGINE SUCCESSFULLY INITIALIZES
	if (gameEngine->init()) {
		playState * test1 = new playState();
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