#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "player.hh"
#include "sprite.hh"

class bullet : public sprite {

public:

	bullet(int, int, int);

	void update(float);

private:

	int direction;

};