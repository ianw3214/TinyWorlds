#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hh"
#include "enemy.hh"
#include "bigEnemy.hh"
#include "animatedSprite.hh"

enum animationState {
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	RUN_RIGHT = 2,
	RUN_LEFT = 3,
	ATTACK1 = 4,
	FALLING = 5,
	IDLE_DEATH = 6
};


constexpr int HORIZONTAL_SPEED = 300;
constexpr int VERTICAL_SPEED = 200;
constexpr int STARTING_HEALTH = 5;

class player : public sprite {

public:

	player();

	void update(float);
	void render(SDL_Surface*, SDL_Rect);

	int getHealth();

	void eventHandler(SDL_Event e);
	void stopMovement();

	void attack(const std::vector<enemy*>&, const std::vector<bigEnemy*>&);
	void attack2(const std::vector<enemy*>&, const std::vector<bigEnemy*>&);
	bool takeDamage(int);
	void die();

private:

	animationState currentState;
	std::vector<int> animSequences;

	int t_width, t_height, c_frame;
	std::vector<int> animationSequences;
	float c_time;
	bool LEFT, RIGHT, UP, DOWN;
	int DIRECTION;		// DIRECTION: direction the player is facing (0-left, 1-right)
	bool attacking;
	float attack2_CD;

	int health;

	std::vector<sprite*> animations;

	// private methods
	void resetAnimation();

};