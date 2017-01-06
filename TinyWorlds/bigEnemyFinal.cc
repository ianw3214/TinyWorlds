#include "bigEnemyFinal.hh"

// default constructor
bigEnemyFinal::bigEnemyFinal(int lastHealth, int inp_x, int inp_y) : bigEnemy() {

	// INITIALIZE VARIABLES
	animationSequences = { 4, 4, 4 };
	this->currentState = FINAL_STATE1;
	this->c_frame = 0;
	this->c_time = 0.0;
	this->t_width = 80, this->t_height = 80;
	this->upgradeTime = 0.0;
	this->moveTime = 0;
	this->cDirection = rand() % 7;

	this->health = lastHealth;		// five the enemy extra health when it upgrades
	this->setPos(inp_x, inp_y);
	this->upgrade = false;
	this->bloomCounter = 0;

	// reset the image source
	std::string path = "assets/enemy2_final.png";
	img = IMG_Load(path.c_str());
	if (!img) {
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

}

// OVERRIDE UPDATE FUNCTION 
void bigEnemyFinal::update(float delta) {

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
		currentState = FINAL_DEATH;
	}

	// update Big Enemy collision rect
	setCollisionRect(60, 60);

	// update big enemy state
	if (upgradeTime >= 5.0) {
		if (currentState = FINAL_STATE1) {
			currentState = FINAL_STATE2;
		}
		else { 
			currentState = FINAL_STATE2;
			if (bloomCounter > 1) {
				bloom = true;
			}
			else {
				bloomCounter++;
			}
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
			if (currentState == FINAL_DEATH) {
				DELETE = true;
				std::cout << "FLAG" << std::endl;
			}
			c_frame = 0;
		}
		c_time = 0.0;
		// update the blitting rect
		this->blitRect = { c_frame * t_width, currentState * t_height, t_width, t_height };
	}

}

// OVERRIDE KILL FUNCTION
void bigEnemyFinal::kill() {

	currentState = FINAL_DEATH;
	c_frame = 0;
	dead = true;

}