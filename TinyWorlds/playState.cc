#include "playState.hh"

// DEFAULT CONSTRUCTOR
playState::playState() {

}

void playState::init() {

	// initialize variables
	lTime = SDL_GetTicks(), cTime = lTime;
	delta = 0.0;
	changeState = false;
	nextState = nullptr;

	// initialize camera
	this->camera = {0, 0, 800, 600};

	// Add the player
	mainPlayer = new player();
	sprites.push_back(mainPlayer);

}

void playState::close() {

}

void playState::handleEvents(bool& running) {

	SDL_Event e;

	// check to see if the player quits the game
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}else if(e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}
		// run an event handler on objects affected by player input
		mainPlayer->eventHandler(e);
	}

}

void playState::update() {

	// update the delta time between updates
	cTime = SDL_GetTicks();
	delta = (cTime - lTime)/1000.0;

	// update all sprites in the sprite list
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->update(delta);
	}

	// update the camera position
	updateCamera();

	// update the previous time
	lTime = cTime;

}

void playState::render(SDL_Surface * display) {

	// Fill the window black before updating the screen
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));

	// update all sprites in the sprite list
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->render(display, camera);
	}

}

void playState::updateCamera() {

	// update the camera based on player position
	camera.x = mainPlayer->getX() - 380;
	std::cout << camera.x << std::endl;

	// check if the camera goes out of bounds
	if (camera.x < 0) {
		camera.x = 0;
	}
	else if (camera.x > 2000 - camera.w) {
		camera.x = 2000 - camera.w;
	}

}