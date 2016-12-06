#include "player.hh"

player::player() : sprite("assets/player.png") {

	// INITIALIZE VARIABLES
	this->animationSequences = { 3, 3, 3, 3 };
	this->currentState = IDLE_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 40, this->t_height = 40;

}

// UPDATE FUNCTION 
void player::update(float delta) {

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

	// update the player position depending on input movement
	if (LEFT) {	this->x -= HORIZONTAL_SPEED * delta; }
	if (RIGHT) { this->x += HORIZONTAL_SPEED * delta; }
	if (UP) { this->y -= VERTICAL_SPEED * delta; }
	if (DOWN) { this->y += VERTICAL_SPEED * delta; }

	std::cout << delta << std::endl;

}

// SPRITE RENDER FUNCTION
void player::render(SDL_Surface * display) {

	SDL_Rect targetRect = { x, y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}

// EVENT HANDLING FUNCTION
void player::eventHandler(SDL_Event e) {

	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT: {
			this->LEFT = true;
			currentState = RUN_LEFT;
		} break;
		case SDLK_RIGHT: {
			this->RIGHT = true;
			currentState = RUN_RIGHT;
		} break;
		case SDLK_DOWN: {
			this->DOWN = true;
		} break;
		case SDLK_UP: {
			this->UP = true;
		} break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT: {
			this->LEFT = false;
			currentState = IDLE_LEFT;
		} break;
		case SDLK_RIGHT: {
			this->RIGHT = false;
			currentState = IDLE_RIGHT;
		} break;
		case SDLK_DOWN: {
			this->DOWN = false;
		} break;
		case SDLK_UP: {
			this->UP = false;
		} break;
		}
	}

}