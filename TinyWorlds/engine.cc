#include "engine.hh"

// default constructor
engine::engine() {
	
}

void engine::setState(gameState * state) {
	
	if (currentState != nullptr) {
		currentState->close();
	}
	this->currentState = state;
	currentState->init();

}

// functions calls to game states
void engine::handleEvents() {
	currentState->handleEvents(running);
}

void engine::update() {
	currentState->update();
	// Check to see if the current game state should be changed
	if (currentState->getChangeState()) {
		gameState * nextState = currentState->getNextState();
		// if the game state should be changed but there is no next state,
		// quit the game
		if (nextState == nullptr) {
			running = false;
		}
		// otherwise, change to the new current state
		else {
			currentState->close();
			this->currentState = nextState;
			currentState->init();
		}
	}
}

void engine::render() {
	currentState->render(display);
	SDL_UpdateWindowSurface(gWindow);
}

// engine initialization
bool engine::init() {
	/*	initializes SDL subsystems and engine variables
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

	// INITIALIZE GAME ENGINE VARIABLES
	this->running = true;

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