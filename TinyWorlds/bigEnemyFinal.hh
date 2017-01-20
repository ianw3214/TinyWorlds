#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "bigEnemy.hh"

enum bigEnemyFinalAnimationState {
	FINAL_STATE1,
	FINAL_STATE2,
	FINAL_DEATH
};

class bigEnemyFinal : public bigEnemy {

public:
	bigEnemyFinal(int, int, int, std::string);

	void update(float);
	void kill();

private:

	bigEnemyFinalAnimationState currentState;

	int bloomCounter;

};