#include "engine.hh"

// default constructor
engine::engine() {

}

// engine initialization
bool engine::init() {
	/*	initializes SDL subsystems
		- returns true/false based on success of initialization
	*/

	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		success = false;
	}
	else {
		// SDL initialization was successful
		gWindow = SDL_CreateWindow("GAME TITLE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr) {
			success = false;
		}
		else {
			// window successfully created
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags)) {
				success = false;
			}
			else {
				// get the window surface
				display = SDL_GetWindowSurface(gWindow);
			}

			// initialize mixer(audio) loading
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				success = false;
			}
		}
	}

	return success;

}

// engine exit function
void engine::close() {

	// Destroy the window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// quit SDL_mixer
	Mix_CloseAudio();

	// Quit SDL subsystems
	SDL_Quit();

}