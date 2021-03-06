#include "enemy.hh"

enemy::enemy(std::string path) : sprite(path) {

	// INITIALIZE VARIABLES
	this->animationSequences = { 3, 3, 3, 3 };
	this->currentState = E_RUN_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 40, this->t_height = 40;

	this->health = 1;

}

int enemy::getHealth() { return this->health; }
bool enemy::getDead() { return this->dead; }

// UPDATE FUNCTION 
void enemy::update(float delta, int p_x, int p_y) {

	// move the enemy 
	move(p_x, p_y, delta);

	// update enemy collision rect
	setCollisionRect(40, 40);

	// Determine the current animation state
	int animationKey = animationSequences[currentState];

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.33) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			if (currentState == DEATH || currentState == EXPLODE) {
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
void enemy::render(SDL_Surface * display, SDL_Rect camera) {

	SDL_Rect targetRect = { x - camera.x, y - camera.y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}


// DAMAGE TAKING FUNCTION
bool enemy::takeDamage(int damage) {
	// returns TRUE if the enemy is still alive, returns false if the enemy
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

// MOVE FUNCTION OF ENEMY DEPENDING ON PLAYER POSITION
void enemy::move(int p_x, int p_y, float delta) {
	// takes player position as input and updates enemy position accordingly
	if (!dead) {
		if (p_x > x) {
			currentState = E_RUN_RIGHT;
			if (x + ENEMY_HORIZONTAL_SPEED*delta > p_x) {
				x = p_x;
			}
			else {
				x += ENEMY_HORIZONTAL_SPEED*delta;
			}
		}
		if (p_x < x) {
			currentState = E_RUN_LEFT;
			if (x - ENEMY_HORIZONTAL_SPEED*delta < p_x) {
				x = p_x;
			}
			else {
				x -= ENEMY_HORIZONTAL_SPEED*delta;
			}
		}
		if (p_y > y) {
			if (y + ENEMY_VERTICAL_SPEED*delta > p_y) {
				y = p_y;
			}
			else {
				y += ENEMY_VERTICAL_SPEED*delta;
			}
		}
		if (p_y < y) {
			if (y - ENEMY_VERTICAL_SPEED*delta < p_y) {
				y = p_y;
			}
			else {
				y -= ENEMY_VERTICAL_SPEED*delta;
			}
		}
	}
	else if(currentState != EXPLODE){
		currentState = DEATH;
	}
}

// explodes when enemy hits the player
void enemy::explode() {

	currentState = EXPLODE;
	c_frame = 0;
	dead = true;

}