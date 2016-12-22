#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hh"

#ifndef anim
#define anim 1
enum animationState {
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	RUN_RIGHT = 2,
	RUN_LEFT = 3
};

#endif

constexpr int HORIZONTAL_SPEED = 300;
constexpr int VERTICAL_SPEED = 200;

class player : public sprite {

public:

	player();

	void update(float);
	void render(SDL_Surface*, SDL_Rect);

	void eventHandler(SDL_Event e);

private:

	animationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;
	bool LEFT, RIGHT, UP, DOWN;

};