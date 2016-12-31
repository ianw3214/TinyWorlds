#include "level1.hh"

void level1::init() {

	// Add the background first so it always gets rendered first
	background = new sprite("assets/BG1.png");
	sprites.push_back(background);

	// call superclass constructor
	playState::init();

	// set initial player position
	mainPlayer->setPos(400, 300);

	// TEST ENEMY
	enemy * test = new enemy();
	enemies.push_back(test);

}

void level1::close() {
	playState::close();
}

void level1::handleEvents(bool& quit) {
	playState::handleEvents(quit);
}

void level1::update() {

	playState::update();
	// make sure the player doesn't go out of bounds horizontally
	int curr_x = mainPlayer->getX(), curr_y = mainPlayer->getY();
	if (curr_x < MARGIN) {
		mainPlayer->setPos(MARGIN, curr_y);
	}
	if (curr_x > LEVEL_WIDTH-MARGIN) {
		mainPlayer->setPos(LEVEL_WIDTH-MARGIN, curr_y);
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->update(delta);
	}
}

void level1::render(SDL_Surface* display) {
	playState::render(display);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->render(display, camera);
	}
}