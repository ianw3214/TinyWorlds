#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "gameState.hh"
#include "sprite.hh"

class playState : public gameState{

public:

	playState();

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render(SDL_Surface*);

private:

	SDL_Surface * background;

	Uint32 cTime, lTime;
	float delta;

	std::vector<sprite*> sprites;

};