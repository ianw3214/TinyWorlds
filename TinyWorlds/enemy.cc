#include "enemy.hh"

enemy::enemy() : sprite("assets/enemy.png") {

	// INITIALIZE VARIABLES
	this->animationSequences = { 3, 3, 3, 3 };
	this->currentState = IDLE_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 40, this->t_height = 40;

}

// UPDATE FUNCTION 
void enemy::update(float delta) {

	// Determine the current animation state
	int animationKey = animationSequences[currentState];

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.33) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

}

// SPRITE RENDER FUNCTION
void enemy::render(SDL_Surface * display, SDL_Rect camera) {

	SDL_Rect targetRect = { x - camera.x, y - camera.y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}