#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "sprite.hh"
#include "animatedSprite.hh"

enum BOSS_animationState {
	BOSS_IDLE_RIGHT = 0,
	BOSS_IDLE_LEFT = 1,
	BOSS_RUN_RIGHT = 2,
	BOSS_RUN_LEFT = 3,
	BOSS_ATTACK1 = 4,
	BOSS_FALLING = 5,
	BOSS_IDLE_DEATH = 6
};

class boss : public sprite {

public:

	boss();

	void update(float);
	void render(SDL_Surface*, SDL_Rect);

	int getHealth();
	bool getDead();

	void stopMovement();

	bool takeDamage(int);
	void die();

	void playSound();

private:

	BOSS_animationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;
	bool LEFT, RIGHT, UP, DOWN;
	int DIRECTION;		// DIRECTION: direction the player is facing (0-left, 1-right)
	int cDirection;	// 0-LEFT 1-ULEFT 2-UP 3-URIGHT 4-RIGHT 5-DRIGHT 6-DOWN 7-DLEFT
	float moveTime;

	int health;
	bool invincible;
	float invincible_CD;
	bool dead;

	std::vector<sprite*> animations;

	// private methods
	void resetAnimation();

};