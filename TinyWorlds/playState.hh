#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "gameState.hh"

class playState : public gameState{

public:

	playState();

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render();

private:

	SDL_Surface * background;

};