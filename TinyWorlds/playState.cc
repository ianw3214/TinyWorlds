#include "playState.hh"

// DEFAULT CONSTRUCTOR
playState::playState() {

}

void playState::init() {

}

void playState::close() {

}

void playState::handleEvents(bool& running) {

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
	}

}

void playState::update() {

}

void playState::render() {

}