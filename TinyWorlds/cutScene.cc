#include "cutScene.hh"

cutScene::cutScene(std::string path, gameState * nextState) {

	background = new sprite(path);
	text = new sprite("assets/cutscenes/text.png");

	this->nextState = nextState;

}

void cutScene::init() {

}

void cutScene::close() {

}

void cutScene::handleEvents(bool& running) {

	SDL_Event e;

	// check to see if the player quits the game
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
			if (e.key.keysym.sym == SDLK_SPACE) {
				changeState = true;
			}
		}
	}

}

void cutScene::update() {

	// update the delta time between updates
	cTime = SDL_GetTicks();
	delta = static_cast<float>((cTime - lTime) / 1000.0);

	// update the previous time
	lTime = cTime;

}

void cutScene::render(SDL_Surface * display) {

	// Fill the window black before updating the WINDOW
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));

	background->render(display, {});
	text->render(display, {});

}