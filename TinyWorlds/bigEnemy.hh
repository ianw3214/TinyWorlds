#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "sprite.hh"

enum bigEnemyAnimationState {
	STATE1,
	STATE2,
	STATE3,
	BIG_DEATH
};


constexpr int BIG_ENEMY_VERTICAL_SPEED = 100;
constexpr int BIG_ENEMY_HORIZONTAL_SPEED = 100;

class bigEnemy : public sprite {

public:

	bigEnemy();

	void update(float);
	void render(SDL_Surface*, SDL_Rect);

	int getHealth();
	bool getDead();

	bool takeDamage(int);
	void kill();

private:

	bigEnemyAnimationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;

	float upgradeTime;
	int cDirection;	// 0-LEFT 1-ULEFT 2-UP 3-URIGHT 4-RIGHT 5-DRIGHT 6-DOWN 7-DLEFT
	float moveTime;

	int health;
	bool dead;

};