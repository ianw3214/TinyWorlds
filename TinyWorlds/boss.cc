#include "boss.hh"

boss::boss() : sprite("assets/player/boss.png") {

	// INITIALIZE VARIABLES
	this->animationSequences = { 8, 8, 6, 3, 5, 5, 3 };
	this->currentState = BOSS_IDLE_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 80, this->t_height = 80;
	this->DIRECTION = 1;
	this->invincible = false;
	this->invincible_CD = 0.0;
	this->dead = false;

	this->health = 12;

}

// getter functions
int boss::getHealth() { return this->health; }
bool boss::getDead() { return this->dead; }

// UPDATE FUNCTION 
void boss::update(float delta) {

	// update boss movement
	// move the big enemy randomly
	if (moveTime > 1.5) {	// if the big enemy has moved long enough in 1 direction
							// Change directions
		cDirection = rand() % 7;
		moveTime = 0;
	}
	else if(!dead) {
		// update position depending on direction
		bool LEFT = false, RIGHT = false, UP = false, DOWN = false;
		switch (cDirection) {
		case 0: {
			LEFT = true;
			currentState = BOSS_RUN_LEFT;
		} break;
		case 1: {
			LEFT = true;
			UP = true;
			currentState = BOSS_RUN_LEFT;
		} break;
		case 2: {
			UP = true;
			currentState = BOSS_RUN_LEFT;
		} break;
		case 3: {
			UP = true;
			RIGHT = true;
			currentState = BOSS_RUN_RIGHT;
		} break;
		case 4: {
			RIGHT = true;
			currentState = BOSS_RUN_RIGHT;
		} break;
		case 5: {
			RIGHT = true;
			DOWN = true;
			currentState = BOSS_RUN_RIGHT;
		} break;
		case 6: {
			DOWN = true;
			currentState = BOSS_RUN_RIGHT;
		} break;
		case 7: {
			DOWN = true;
			LEFT = true;
			currentState = BOSS_RUN_LEFT;
		} break;
		}
		// MOVE THE ENEMY AND CHECK IF IT IS OUT OF BOUNDS
		if (UP) { y -= 200 * delta; }
		if (DOWN) { y += 200 * delta; }
		if (LEFT) { x -= 300 * delta; }
		if (RIGHT) { x += 300 * delta; }
		if (x < 70) { x = 70; }
		if (x > 1930) { x = 1930; }
		if (y < 280) { y = 280; }
		if (y > 530) { y = 530; }

		moveTime += delta;
	}

	// Determine the current animation state
	int animationKey = animationSequences[currentState];

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.05 && currentState != BOSS_FALLING) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			if (currentState == BOSS_FALLING) {
				currentState = BOSS_IDLE_DEATH;
			}
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}
	else if (currentState == BOSS_FALLING && c_time > 0.5) {	// if the character is currently falling
		c_frame++;
		if (c_frame >= animationKey) {
			currentState = BOSS_IDLE_DEATH;
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

	// update each additional animation of the player
	for (int i = animations.size() - 1; i >= 0; i--) {
		animations.at(i)->update(delta);
		// delete the animation if it is over
		if (animations.at(i)->GET_DELETE()) {
			animations.erase(animations.begin() + i);
		}
	}

	// update player collision rectangle
	this->collisionRect = { x+20, y+10, 40, 60 };

	// update invincible cooldown times
	if (invincible_CD != 0.0) {
		invincible_CD -= delta;
		if (invincible_CD < 0.0) {
			invincible_CD = 0.0;
		}
	}
	else {
		invincible = false;
	}

}

// SPRITE RENDER FUNCTION
void boss::render(SDL_Surface * display, SDL_Rect camera) {

	SDL_Rect targetRect = { x - camera.x, y - camera.y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

	// render each additional animation of the player
	for (int i = animations.size() - 1; i >= 0; i--) {
		animations.at(i)->render(display, camera);
	}

}

// STOPS ALL PLAYER MOVEMENT
void boss::stopMovement() {

	UP = false, DOWN = false, LEFT = false, RIGHT = false;

}

// DAMAGE TAKING FUNCTION
bool boss::takeDamage(int damage) {
	// returns TRUE if the player is still alive, returns false if the player
	// is dead

	// make sure to only take damage if the player isn't invincible
	if (!invincible) {
		// if the player takes damage, set up a damage cooldown
		this->health -= damage;
		this->invincible = true;
		this->invincible_CD = 1.0;

		if (this->health > 0) {
			return true;
		}

		return false;

	}
	else {
		return true;
	}

}

// PLAYER KILL FUNCTION
void boss::die() {

	if (!dead) {
		dead = true;
		stopMovement();
		c_frame = 0;
		currentState = BOSS_FALLING;
	}

}

// animation reset function
void boss::resetAnimation() {
	// first check if the player is moving
	if (UP || DOWN || LEFT || RIGHT) {
		if (DIRECTION == 0) {
			currentState = BOSS_RUN_LEFT;
		}
		else {
			currentState = BOSS_RUN_RIGHT;
		}
	}
	// otherwise play the idle animation
	else {
		if (DIRECTION == 0) {
			currentState = BOSS_IDLE_LEFT;
		}
		else {
			currentState = BOSS_IDLE_RIGHT;
		}
	}
}

void boss::playSound() {

	// SDL_Mixer variable to hold the music file
	Mix_Chunk *tempWave = Mix_LoadWAV("music/attack.wav");
	// check to see if the music successfully loaded
	if (tempWave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_PlayChannel(1, tempWave, 0) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
	return;

}