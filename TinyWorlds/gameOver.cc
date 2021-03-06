#include "gameOver.hh"

// empty default constructor
gameOver::gameOver(bool mute, Mix_Chunk * wav) {
	if (mute) {
		this->mute = mute;
	}
	if (wav) {
		this->wave = wav;
	}
}

// initialization function
void gameOver::init() {

	// initialize variables
	lTime = SDL_GetTicks(), cTime = lTime;
	delta = 0.0;
	changeState = false;
	nextState = nullptr;

	// add the background
	background = new sprite("assets/gameover.png");

}

void gameOver::close() {
	// close the music
	Mix_FadeOutMusic(10);
	Mix_FreeChunk(wave);
}

void gameOver::handleEvents(bool& running) {

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
				nextState = new mainMenu();
				changeState = true;
			}
		}
	}

}

void gameOver::update() {

	// update the delta time between updates
	cTime = SDL_GetTicks();
	delta = static_cast<float>((cTime - lTime) / 1000.0);

	// update the previous time
	lTime = cTime;

}

void gameOver::render(SDL_Surface * display) {

	// Fill the window black before updating the WINDOW
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));

	background->render(display, {});

}