#include "playState.hh"

// DEFAULT CONSTRUCTOR
playState::playState() {

}

void playState::init() {

	// initialize variables
	lTime = SDL_GetTicks(), cTime = lTime;
	delta = 0.0;

	// TESTING SPRITE
	animatedSprite * temp = new animatedSprite("assets/TEST_SS.png", 40, 40, 5);
	temp->setPos(10, 10);
	sprites.push_back(temp);

	for (unsigned int i = 0; i < 20; i ++) {
		animatedSprite * temp2 = new animatedSprite("assets/TEST_SS.png", 40, 40, 5);
		temp2->setPos(100, i*40);
		sprites.push_back(temp2);
	}

	mainPlayer = new player();
	sprites.push_back(mainPlayer);

}

void playState::close() {

}

void playState::handleEvents(bool& running) {

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
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

	// update the previous time
	lTime = cTime;

}

void playState::render(SDL_Surface * display) {

	// Fill the window black before updating the screen
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));

	// update all sprites in the sprite list
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->render(display);
	}

}