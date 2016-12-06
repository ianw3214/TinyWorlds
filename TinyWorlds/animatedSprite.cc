#include "animatedSprite.hh"

// DEFAULT CONSTRUCTOR
animatedSprite::animatedSprite(std::string path, int t_width, int t_height, int frames) : sprite(path) {

	// initialize variables
	this->c_frame = 0;
	this->num_frames = frames;
	this->c_time = 0.0;
	this->t_width = t_width, this->t_height = t_height;

	// initialize blitting rect to the first frame
	this->blitRect = {0, 0, t_width, t_height};

}

// UPDATE FUNCTION 
void animatedSprite::update(float delta) {

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.033) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= num_frames) {
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = {c_frame * t_width, 0, t_width, t_height};
	}

}

void animatedSprite::render(SDL_Surface * display) {

	SDL_Rect targetRect = {x, y, 0, 0};
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}