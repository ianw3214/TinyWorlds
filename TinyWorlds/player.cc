#include "player.hh"

player::player() : sprite("assets/player.png") {

	// INITIALIZE VARIABLES
	this->animationSequences = { 3, 3, 3, 3 };
	this->currentState = IDLE_RIGHT;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 40, this->t_height = 40;
	this->DIRECTION = 1;

	this->health = STARTING_HEALTH;

}

// UPDATE FUNCTION 
void player::update(float delta) {

	// update player sprite animation
	if (!UP && !LEFT && !RIGHT && !DOWN) {
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
	if (c_time > 0.33) {
		// update the current sprite frame
		c_frame++;
		if (c_frame >= animationKey) {
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

	// update the player position depending on input movement
	
	if (LEFT) {	this->x -= static_cast<int>(HORIZONTAL_SPEED * delta); }
	if (RIGHT) { this->x += static_cast<int>(HORIZONTAL_SPEED * delta); }
	if (UP) { this->y -= static_cast<int>(VERTICAL_SPEED * delta); }
	if (DOWN) { this->y += static_cast<int>(VERTICAL_SPEED * delta); }
	
	// update each additional animation of the player
	for (int i = animations.size() - 1; i >= 0; i--) {
		animations.at(i)->update(delta);
		// delete the animation if it is over
		if (animations.at(i)->GET_DELETE()) {
			animations.erase(animations.begin()+i);
		}
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
			this->currentState = RUN_LEFT;
			this->DIRECTION = 0;
			this->LEFT = true;
		} break;
		case SDLK_RIGHT: {
			this->currentState = RUN_RIGHT;
			this->DIRECTION = 1;
			this->RIGHT = true;
		} break;
		case SDLK_DOWN: {
			this->DOWN = true;
			if (DIRECTION == 0) {
				this->currentState = RUN_LEFT;
			}
			else {
				this->currentState = RUN_RIGHT;
			}
		} break;
		case SDLK_UP: {
			this->UP = true;
			if (DIRECTION == 0) {
				this->currentState = RUN_LEFT;
			}
			else {
				this->currentState = RUN_RIGHT;
			}
		} break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_LEFT: {
			this->LEFT = false;
			if (RIGHT) {
				this->currentState = RUN_RIGHT;
				this->DIRECTION = 1;
			}
		} break;
		case SDLK_RIGHT: {
			this->RIGHT = false;
			if (LEFT) {
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

// ATTACK FUNCTION
void player::attack(const std::vector<enemy*>& enemies) {
	// takes a list of enemies as input and updates them if they are hit

	// first make a rectangle based on the players direction that will act
	// as the collision hitbox
	SDL_Rect collision_box = {};
	if (DIRECTION == 1) {	// RIGHT
		collision_box = { x, y, 60, 40 };
		// create a visual sprite to represent the attack
		animatedSprite * attack = new animatedSprite("assets/attack1.png", 60, 40, 8, true);
		attack->setPos(x, y);
		animations.push_back(attack);
	}
	else {					// LEFT
		collision_box = { x-20, y, 60, 40 };
		// create a visual sprite to represent the attack
		animatedSprite * attack = new animatedSprite("assets/attack1.png", 60, 40, 8, true);
		attack->setPos(x-20, y);
		animations.push_back(attack);
	}
	
	// check collision with each enemy
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if(SDL_HasIntersection(&enemies.at(i)->getCollisionRect(), &collision_box)){
			enemies.at(i)->takeDamage(1);
		}
	}
	

	std::cout << "ATTACK" << std::endl;

}

// DAMAGE TAKING FUNCTION
bool player::takeDamage(int damage) {
	// returns TRUE if the player is still alive, returns false if the player
	// is dead
	
	this->health -= damage;
	
	if (this->health > 0) {
		return true;
	}

	return false;

}