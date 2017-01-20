#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "gameState.hh"
#include "sprite.hh"
#include "animatedSprite.hh"
#include "mainMenu.hh"

class gameOver : public gameState {

public:
	gameOver(bool mute = false, Mix_Chunk * wav = nullptr);

	virtual void init();
	virtual void close();

	virtual void handleEvents(bool&);
	virtual void update();
	virtual void render(SDL_Surface*);

protected:

	sprite * background;

	Uint32 cTime, lTime;
	float delta;

	bool mute;
	Mix_Chunk *wave;

};