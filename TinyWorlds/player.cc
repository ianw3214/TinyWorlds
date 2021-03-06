#include "player.hh"

player::player() : sprite("assets/player/player.png") {

	// INITIALIZE VARIABLES
	this->animationSequences = { 8, 8, 6, 3, 5, 5, 3 };
	this->currentState = IDLE_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 80, this->t_height = 80;
	this->DIRECTION = 1;
	this->attacking = false;
	this->attack1_CD = 0.0;
	this->attack2_CD = 0.0;
	this->invincible = false;
	this->invincible_CD = 0.0;

	this->health = STARTING_HEALTH;
	std::cout << "FLAG" << std::endl;

}

// getter functions
int player::getHealth() { return this->health; }

// UPDATE FUNCTION 
void player::update(float delta) {

	// update player sprite animation
	if (!UP && !LEFT && !RIGHT && !DOWN && !attacking && currentState != FALLING && currentState != IDLE_DEATH) {
		if (DIRECTION == 0) {
			this->currentState = IDLE_LEFT;
		}
		else {
			this->currentState = IDLE_RIGHT;
		}
	}
	
	// Determine the current animation state
	int animationKey = animationSequences[currentState];

	c_time += delta;
	// update at a rate of 30 fps
	if (c_time > 0.05 && currentState != FALLING) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			if (currentState == ATTACK1) {
				attacking = false;
				resetAnimation();
			}
			if (currentState == FALLING) {
				currentState = IDLE_DEATH;
			}
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}
	else if(currentState == FALLING && c_time > 0.5){	// if the character is currently falling
		c_frame++;
		if (c_frame >= animationKey) {
			currentState = IDLE_DEATH;
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

	// update the player position depending on input movement
	
	if (LEFT && !attacking) {	this->x -= static_cast<int>(HORIZONTAL_SPEED * delta); }
	if (RIGHT && !attacking) { this->x += static_cast<int>(HORIZONTAL_SPEED * delta); }
	if (UP && !attacking) { this->y -= static_cast<int>(VERTICAL_SPEED * delta); }
	if (DOWN && !attacking) { this->y += static_cast<int>(VERTICAL_SPEED * delta); }
	
	// update each additional animation of the player
	for (int i = animations.size() - 1; i >= 0; i--) {
		animations.at(i)->update(delta);
		// delete the animation if it is over
		if (animations.at(i)->GET_DELETE()) {
			animations.erase(animations.begin()+i);
		}
	}

	// update player collision rectangle
	this->collisionRect = { x + 20, y + 10, 40, 60 };

	// update player cooldown times
	if (attack2_CD != 0.0) {
		attack2_CD -= delta;
		if (attack2_CD < 0.0) {
			attack2_CD = 0.0;
		}
	}
	if (attack1_CD != 0.0) {
		attack1_CD -= delta;
		if (attack1_CD < 0.0) {
			attack1_CD = 0.0;
		}
	}

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
void player::render(SDL_Surface * display, SDL_Rect camera) {

	SDL_Rect targetRect = { x - camera.x, y-camera.y, 0, 0 };
	if (SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

	// render each additional animation of the player
	for (int i = animations.size() - 1; i >= 0; i--) {
		animations.at(i)->render(display, camera);
	}

}

// EVENT HANDLING FUNCTION
void player::eventHandler(SDL_Event e) {

	// update player flags and animation states based on key presses
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT: {
			if(!attacking) this->currentState = RUN_LEFT;
			this->DIRECTION = 0;
			this->LEFT = true;
		} break;
		case SDLK_RIGHT: {
			if (!attacking) this->currentState = RUN_RIGHT;
			this->DIRECTION = 1;
			this->RIGHT = true;
		} break;
		case SDLK_DOWN: {
			this->DOWN = true;
			if (DIRECTION == 0 && !attacking) {
				this->currentState = RUN_LEFT;
			}
			else if(!attacking){
				this->currentState = RUN_RIGHT;
			}
		} break;
		case SDLK_UP: {
			this->UP = true;
			if (DIRECTION == 0 && !attacking) {
				this->currentState = RUN_LEFT;
			}
			else if(!attacking){
				this->currentState = RUN_RIGHT;
			}
		} break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT: {
			this->LEFT = false;
			if (RIGHT && !attacking) {
				this->currentState = RUN_RIGHT;
				this->DIRECTION = 1;
			}
		} break;
		case SDLK_RIGHT: {
			this->RIGHT = false;
			if (LEFT && !attacking) {
				this->currentState = RUN_LEFT;
				this->DIRECTION = 0;
			}
		} break;
		case SDLK_DOWN: {
			this->DOWN = false;
		} break;
		case SDLK_UP: {
			this->UP = false;
		} break;
		}
	}

}

// STOPS ALL PLAYER MOVEMENT
void player::stopMovement() {

	UP = false, DOWN = false, LEFT = false, RIGHT = false;

}

// ATTACK FUNCTION
void player::attack(const std::vector<enemy*>& enemies, const std::vector<bigEnemy*>& bigEnemies) {
	// takes a list of enemies as input and updates them if they are hit

	if (attack1_CD == 0.0) {

		playSound();

		attack1_CD = 0.4;

		// first make a rectangle based on the players direction that will act
		// as the collision hitbox
		SDL_Rect collision_box = {};
		if (DIRECTION == 1) {	// RIGHT
			collision_box = { x, y - 40, 240, 160 };
			// create a visual sprite to represent the attack
			animatedSprite * attack = new animatedSprite("assets/player/attack1_flip.png", 240, 160, 8, true);
			attack->setPos(x, y - 40);
			animations.push_back(attack);
		}
		else {					// LEFT
			collision_box = { x - 160, y - 40, 240, 160 };
			// create a visual sprite to represent the attack
			animatedSprite * attack = new animatedSprite("assets/player/attack1.png", 240, 160, 8, true);
			attack->setPos(x - 160, y - 40);
			animations.push_back(attack);
		}

		// check collision with each enemy
		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (SDL_HasIntersection(&enemies.at(i)->getCollisionRect(), &collision_box)) {
				enemies.at(i)->takeDamage(1);
			}
		}
		// check collision with each big enemy
		for (unsigned int i = 0; i < bigEnemies.size(); i++) {
			if (SDL_HasIntersection(&bigEnemies.at(i)->getCollisionRect(), &collision_box)) {
				bigEnemies.at(i)->takeDamage(1);
			}
		}

		// update player animation and stop movement
		c_frame = 0;
		currentState = ATTACK1;
		attacking = true;

	}

}

// ATTACK FUNCTION
void player::attack2(const std::vector<enemy*>& enemies, const std::vector<bigEnemy*>& bigEnemies) {
	// takes a list of enemies as input and updates them if they are hit

	// FIRST CHECK THE COOLDOWN 
	if (attack2_CD == 0.0) {

		playSound();

		// reset the cooldown
		attack2_CD = 1.0;

		// first make a rectangle based on the players direction that will act
		// as the collision hitbox
		SDL_Rect collision_box = { x - 120, y - 100, 560, 320 };
		// create a visual sprite to represent the attack
		animatedSprite * attack = new animatedSprite("assets/player/attack2.png", 560, 320, 8, true);
		attack->setPos(x - 120, y - 180);
		animations.push_back(attack);

		// check collision with each enemy
		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (SDL_HasIntersection(&enemies.at(i)->getCollisionRect(), &collision_box)) {
				enemies.at(i)->takeDamage(1);
			}
		}
		// check collision with each big enemy
		for (unsigned int i = 0; i < bigEnemies.size(); i++) {
			if (SDL_HasIntersection(&bigEnemies.at(i)->getCollisionRect(), &collision_box)) {
				bigEnemies.at(i)->takeDamage(1);
			}
		}

		// update player animation and stop movement
		c_frame = 0;
		currentState = ATTACK1;
		attacking = true;

	}
	
}

// ATTACK FUNCTION
void player::attack1(boss* finalBoss) {
	// takes a list of enemies as input and updates them if they are hit

	if (attack1_CD == 0.0) {

		playSound();

		attack1_CD = 0.4;

		// first make a rectangle based on the players direction that will act
		// as the collision hitbox
		SDL_Rect collision_box = {};
		if (DIRECTION == 1) {	// RIGHT
			collision_box = { x, y - 40, 240, 160 };
			// create a visual sprite to represent the attack
			animatedSprite * attack = new animatedSprite("assets/player/attack1_flip.png", 240, 160, 8, true);
			attack->setPos(x, y - 40);
			animations.push_back(attack);
		}
		else {					// LEFT
			collision_box = { x - 160, y - 40, 240, 160 };
			// create a visual sprite to represent the attack
			animatedSprite * attack = new animatedSprite("assets/player/attack1.png", 240, 160, 8, true);
			attack->setPos(x - 160, y - 40);
			animations.push_back(attack);
		}

		// check collision with each enemy
		if (SDL_HasIntersection(&finalBoss->getCollisionRect(), &collision_box)) {
			if (!finalBoss->takeDamage(1)) {
				finalBoss->die();
			}
		}

		// update player animation and stop movement
		c_frame = 0;
		currentState = ATTACK1;
		attacking = true;

	}

}

// ATTACK FUNCTION
void player::attack2(boss* finalBoss) {
	// takes a list of enemies as input and updates them if they are hit

	// FIRST CHECK THE COOLDOWN 
	if (attack2_CD == 0.0) {

		playSound();

		// reset the cooldown
		attack2_CD = 3.0;

		// first make a rectangle based on the players direction that will act
		// as the collision hitbox
		SDL_Rect collision_box = { x - 120, y - 100, 560, 320 };
		// create a visual sprite to represent the attack
		animatedSprite * attack = new animatedSprite("assets/player/attack2.png", 560, 320, 8, true);
		attack->setPos(x - 120, y - 180);
		animations.push_back(attack);

		// check collision with each enemy
		if (SDL_HasIntersection(&finalBoss->getCollisionRect(), &collision_box)) {
			finalBoss->takeDamage(1);
		}
		// check collision with each big enemy
		if (SDL_HasIntersection(&finalBoss->getCollisionRect(), &collision_box)) {
			if (!finalBoss->takeDamage(1)) {
				finalBoss->die();
			}
		}

		// update player animation and stop movement
		c_frame = 0;
		currentState = ATTACK1;
		attacking = true;

	}

}

// DAMAGE TAKING FUNCTION
bool player::takeDamage(int damage) {
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
void player::die() {

	stopMovement();
	c_frame = 0;
	currentState = FALLING;

}

// animation reset function
void player::resetAnimation() {
	// first check if the player is moving
	if (UP || DOWN || LEFT || RIGHT) {
		if (DIRECTION == 0) {
			currentState = RUN_LEFT;
		}
		else {
			currentState = RUN_RIGHT;
		}
	}
	// otherwise play the idle animation
	else {
		if (DIRECTION == 0) {
			currentState = IDLE_LEFT;
		}
		else {
			currentState = IDLE_RIGHT;
		}
	}
}

void player::playSound() {

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