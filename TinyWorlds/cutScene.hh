#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "gameState.hh"
#include "sprite.hh"

class cutScene : public gameState {

public:

	cutScene(std::string, gameState*);

	virtual void init();
	virtual void close();

	virtual void handleEvents(bool&);
	virtual void update();
	virtual void render(SDL_Surface*);

protected:

	sprite * background;
	sprite * text;

	Uint32 cTime, lTime;
	float delta;

};