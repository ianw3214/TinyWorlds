#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "sprite.hh"

enum enemyAnimationState {
	E_RUN_RIGHT,
	E_RUN_LEFT,
	DEATH,
	EXPLODE
};


constexpr int ENEMY_VERTICAL_SPEED = 100;
constexpr int ENEMY_HORIZONTAL_SPEED = 100;

class enemy : public sprite {

public:

	enemy();

	void update(float, int, int);
	void render(SDL_Surface*, SDL_Rect);

	int getHealth();
	bool getDead();

	bool takeDamage(int);

	void move(int, int, float);
	void explode();

private:

	enemyAnimationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;

	int health;
	bool dead;

};