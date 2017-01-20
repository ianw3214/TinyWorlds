#include "bigEnemy.hh"

bigEnemy::bigEnemy(std::string path) : sprite(path) {

	// INITIALIZE VARIABLES
	this->animationSequences = { 4, 4, 4, 4, 4, 4 };
	this->currentState = STATE1;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 120, this->t_height = 120;
	this->upgradeTime = 0.0;
	this->moveTime = 0;
	this->cDirection = rand() % 7;

	this->health = 7;
	this->upgrade = false;
	this->bloom = false;

}

int bigEnemy::getHealth() { return this->health; }
bool bigEnemy::getDead() { return this->dead; }
bool bigEnemy::getUpgrade() { return this->upgrade; }
bool bigEnemy::getBloom() { return this->bloom; }

// UPDATE FUNCTION 
void bigEnemy::update(float delta) {

	// update big enemy position if it is not dead
	if (!dead) {
		// move the big enemy randomly
		if (moveTime > 3.0) {	// if the big enemy has moved long enough in 1 direction
			// Change directions
			cDirection = rand() % 7;
			moveTime = 0;
		}
		else {
			// update position depending on direction
			bool LEFT = false, RIGHT = false, UP = false, DOWN = false;
			switch (cDirection) {
			case 0: {
				LEFT = true;
			} break;
			case 1: {
				LEFT = true;
				UP = true;
			} break;
			case 2: {
				UP = true;
			} break;
			case 3: {
				UP = true;
				RIGHT = true;
			} break;
			case 4: {
				RIGHT = true;
			} break;
			case 5: {
				RIGHT = true;
				DOWN = true;
			} break;
			case 6: {
				DOWN = true;
			} break;
			case 7: {
				DOWN = true;
				LEFT = true;
			} break;
			}
			// MOVE THE ENEMY AND CHECK IF IT IS OUT OF BOUNDS
			if (UP) { y -= BIG_ENEMY_VERTICAL_SPEED * delta; }
			if (DOWN) { y += BIG_ENEMY_VERTICAL_SPEED * delta; }
			if (LEFT) { x -= BIG_ENEMY_HORIZONTAL_SPEED * delta; }
			if (RIGHT) { x += BIG_ENEMY_HORIZONTAL_SPEED * delta; }
			if (x < 70) { x = 70; }
			if (x > 1930) { x = 1930; }
			if (y < 280) { y = 280; }
			if (y > 530) { y = 530; }

			moveTime += delta;
		}
	}
	else {
		currentState = BIG_DEATH;
	}

	// update Big Enemy collision rect
	setCollisionRect(120, 120);

	// update big enemy state
	if (upgradeTime >= 7.0) {
		if (currentState == STATE1) {
			currentState = STATE2;
		}
		else if (currentState == STATE2) {
			currentState = STATE3;
		}
		else if(currentState != BIG_DEATH){
			currentState = STATE3;
			upgrade = true;
		}
		upgradeTime = 0.0;
	}
	else {
		upgradeTime += delta;
	}

	// Determine the current animation state
	int animationKey = animationSequences[currentState];

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.33) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			if (currentState == BIG_DEATH) {
				DELETE = true;
			}
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

}

// SPRITE RENDER FUNCTION
void bigEnemy::render(SDL_Surface * display, SDL_Rect camera) {
	
	SDL_Rect targetRect = { x - camera.x, y - camera.y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}


// DAMAGE TAKING FUNCTION
bool bigEnemy::takeDamage(int damage) {
	// returns TRUE if the bigEnemy is still alive, returns false if the bigEnemy
	// is dead

	this->health -= damage;

	if (this->health > 0) {
		return true;
	}

	// reset animation frames and return false if dead
	c_frame = 0;
	dead = true;
	return false;

}

// kill function for the big enemy, called when enemy is dead
void bigEnemy::kill() {

	currentState = BIG_DEATH;
	c_frame = 0;
	dead = true;

}

// kill function for the big enemy, called when enemy is upgraded
void bigEnemy::upgradeKill() {

	currentState = UPGRADE;
	c_frame = 0;
	dead = true;

}