#pragma once

#include <SDL.h>

class gameState {

public:

	gameState();

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void handleEvents(bool&) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Surface*) = 0;

};