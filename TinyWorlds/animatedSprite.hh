/*	ANIMATED SPRITE CLASS

	- assumes all tilesheets are completely horizontal in terms of tiling

*/
#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hh"

class animatedSprite : public sprite {

public:

	animatedSprite(std::string, int, int, int);

	void update(float);
	void render(SDL_Surface*);

protected:

	int t_width, t_height;
	int num_frames, c_frame;
	float c_time;

};