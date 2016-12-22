#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "playState.hh"
#include "enemy.hh"

class level1 : public playState {

public:

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render(SDL_Surface*);

private:

	std::vector<enemy*> enemies;

};