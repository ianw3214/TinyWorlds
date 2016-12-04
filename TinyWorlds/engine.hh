#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "gameState.hh"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

class engine {

public:
	engine();
	bool init();
	void close();

	bool isRunning() const { return running; }

	void setState(gameState*);

	void handleEvents();
	void update();
	void render();

private:

	SDL_Window * gWindow;
	SDL_Surface * display;

	bool running;

	gameState * currentState;
};