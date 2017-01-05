#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hh"

class stillSprite : public sprite {

public:

	stillSprite(std::string path) : sprite(path) {};
	void render(SDL_Surface*, SDL_Rect);

};