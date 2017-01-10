#include "level2.hh"

void level2::init() {

	// Add the sky to always get rendered first
	background = new stillSprite("assets/level2/background2_sky.png");
	sprites.push_back(background);

	// initialize sprites for background parallaxing
	bg = new stillSprite("assets/level2/background2_back.png");
	sprites.push_back(bg);
	mg = new stillSprite("assets/level2/background2_mid.png");
	sprites.push_back(mg);

	// don't push foreground into sprites vector so we can control it's rendering to be last
	fg = new stillSprite("assets/level2/background2_front.png");
	topLevel.push_back(fg);

	// call superclass constructor
	playState::init();

	// initialize variables
	this->enemySpawnCounter = 0.0;
	this->GAME_OVER = false;
	this->winTimer = 0.0;

	// Spawn in the big enemies
	for (int i = 0; i < 5; i++) {
		bigEnemy* temp = new bigEnemy();
		temp->setPos(rand() % 1800 + 100, 400 + rand() % 80 - 40);
		bigEnemies.push_back(temp);
	}

	// set initial player position
	this->mainPlayer->setPos(1000, 300);

}

void level2::close() {
	playState::close();
}

// OVERRIDE the playstate event handler to take on player attacks
void level2::handleEvents(bool& running) {

	SDL_Event e;

	// check to see if the player quits the game
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
			if (e.key.keysym.sym == SDLK_q && !GAME_OVER) {
				mainPlayer->attack(enemies, bigEnemies);
			}
			if (e.key.keysym.sym == SDLK_w && !GAME_OVER) {
				mainPlayer->attack2(enemies, bigEnemies);
			}
			if (e.key.keysym.sym == SDLK_SPACE && GAME_OVER) {
				// move on to the death menu
				changeState = true;

			}
		}
		// run an event handler on objects affected by player input
		if (!GAME_OVER) mainPlayer->eventHandler(e);
	}
}

void level2::update() {

	// update everything only if the game is still running
	if (!GAME_OVER) {

		// update the timer to keep see if the player has won
		winTimer += delta;
		if (winTimer >= 2.0) {
			game_over(2);
		}

		playState::update();
		// make sure the player doesn't go out of bounds horizontally
		int curr_x = mainPlayer->getX(), curr_y = mainPlayer->getY();
		if (curr_x < MARGIN) {
			mainPlayer->setPos(MARGIN, curr_y);
		}
		if (curr_x > LEVEL_WIDTH_2 - MARGIN) {
			mainPlayer->setPos(LEVEL_WIDTH_2 - MARGIN, curr_y);
		}
		// spawn enemies
		handleEnemySpawn(delta);
		// update the enemies last
		for (int i = enemies.size() - 1; i >= 0; i--) {
			enemies.at(i)->update(delta, mainPlayer->getX(), mainPlayer->getY());
			// check for collisions between enemies and player
			if (SDL_HasIntersection(&enemies.at(i)->getCollisionRect(), &mainPlayer->getCollisionRect()) && !enemies.at(i)->getDead()) {
				enemies.at(i)->explode();
				if (!mainPlayer->takeDamage(1)) {
					// if the function returns false, then the player has died
					game_over(0);
				}
			}
			// delete the enemy if it should be deleted
			if (enemies.at(i)->GET_DELETE()) {
				enemies.erase(enemies.begin() + i);
			}
		}

		// update big enemies
		for (int i = bigEnemies.size() - 1; i >= 0; i--) {
			bigEnemies.at(i)->update(delta);
			// delete the enemy if it should be deleted
			if (bigEnemies.at(i)->GET_DELETE()) {
				bigEnemies.erase(bigEnemies.begin() + i);
			}
			// check if the enemy should be upgraded
			else if (bigEnemies.at(i)->getUpgrade()) {
				// add an upgrade sprite
				animatedSprite * temp_FX = new animatedSprite("assets/enemy2_upgrade.png", 60, 60, 8, true);
				temp_FX->setPos(bigEnemies.at(i)->getX(), bigEnemies.at(i)->getY());
				sprites.push_back(temp_FX);
				// make the upgrade
				bigEnemyFinal *temp = new bigEnemyFinal(bigEnemies.at(i)->getHealth(), bigEnemies.at(i)->getX() - 10, bigEnemies.at(i)->getY() - 10);
				bigEnemies.erase(bigEnemies.begin() + i);
				bigEnemies.push_back(temp);
			}
			// if the enemy has bloomed
			else if (bigEnemies.at(i)->getBloom()) {
				// THEN THE GAME IS OVER
				game_over(1);
			}
		}

		// update background parallaxing with respect to player position
		if (camera.x != 0 && camera.x != 2000 - camera.w) {
			// only update background if background is moving (camera is moving)
			bg->setPos(-mainPlayer->getX() / 3, 0);
			mg->setPos(-mainPlayer->getX(), 0);
			fg->setPos(-mainPlayer->getX() * 2, 0);
		}
	}
	else {
		mainPlayer->update(delta);
	}

}

void level2::render(SDL_Surface* display) {
	playState::render(display);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->render(display, camera);
	}
	for (unsigned int i = 0; i < bigEnemies.size(); i++) {
		bigEnemies.at(i)->render(display, camera);
	}
	// render hearts to represent player health
	for (unsigned int i = 0; i < mainPlayer->getHealth(); i++) {
		stillSprite * temp = new stillSprite("assets/heart.png");
		temp->setPos(20 + i * 40, 20);
		temp->render(display, camera);
	}
	// render the top level content
	for (unsigned int i = 0; i < topLevel.size(); i++) {
		topLevel.at(i)->render(display, camera);
	}
}

void level2::handleEnemySpawn(float delta) {

	// update the spawn timer
	enemySpawnCounter += delta;

	if (enemySpawnCounter >= SPAWN_TIME_2) {
		// spawn a new enemy if the timer is reached
		enemy * test = new enemy();
		// make sure the enemy isn't spawned too close to the player
		int init_x = rand() % 1800 + 100;
		int init_y = rand() % 250 + 300;
		while (std::abs(init_x - mainPlayer->getX()) < 200) {
			std::cout << "GENERATING" << std::endl;
			init_x = rand() % 1800 + 100;
			init_y = rand() % 250 + 300;
		}
		test->setPos(init_x, init_y);
		enemies.push_back(test);
		// reset the spawn counter
		enemySpawnCounter = 0.0;
	}

}

// function that handles dealing with game over
void level2::game_over(int key) {
	// Takes different keys to represent different game over states
	// 0 -> GAME LOST BY PLAYER DEATH
	// 1 -> GAME LOST BY ENEMY BLOOM
	// 2 -> GAME WON

	if (key == 0) {

		// THIS MEANS THE PLAYER DIED
		std::cout << "DIED" << std::endl;
		mainPlayer->die();
		GAME_OVER = true;

		// Update the screen
		stillSprite * temp = new stillSprite("assets/text1.png");
		topLevel.push_back(temp);

		// update the next game state to game over
		nextState = new gameOver();

	}
	else if (key == 1) {

		mainPlayer->stopMovement();
		GAME_OVER = true;

		// Update the screen
		stillSprite * temp = new stillSprite("assets/text1.png");
		topLevel.push_back(temp);

		// update the next game state to game over
		nextState = new gameOver();

	}
	else if (key == 2) {

		// The player won the game
		mainPlayer->stopMovement();
		GAME_OVER = true;

		// update the screen
		std::cout << "WIN CONDITION";

	}

}