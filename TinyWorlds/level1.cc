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