#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hh"

enum animationState {
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	RUN_RIGHT = 2,
	RUN_LEFT = 3
};

constexpr int HORIZONTAL_SPEED = 500;
constexpr int VERTICAL_SPEED = 400;

class player : public sprite {

public:

	player();

	void update(float);
	void render(SDL_Surface*);

	void eventHandler(SDL_Event e);
	void setState(animationState);

private:

	animationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;
	bool LEFT, RIGHT, UP, DOWN;

};