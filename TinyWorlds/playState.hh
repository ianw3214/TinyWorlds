#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "gameState.hh"
#include "sprite.hh"
#include "animatedSprite.hh"
#include "player.hh"

class playState : public gameState{

public:

	playState();

	virtual void init();
	virtual void close();
	
	virtual void handleEvents(bool&);
	virtual void update();
	virtual void render(SDL_Surface*);

protected:

	sprite * background;

	SDL_Rect camera;
	void updateCamera();

	Uint32 cTime, lTime;
	float delta;

	std::vector<sprite*> sprites;
	player * mainPlayer;

};