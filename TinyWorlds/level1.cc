#include "level1.hh"

void level1::init() {

	// Add the sky to always get rendered first
	background = new stillSprite("assets/background1_sky.png");
	sprites.push_back(background);

	// initialize sprites for background parallaxing
	bg = new stillSprite("assets/background1_back.png");
	sprites.push_back(bg);
	mg = new stillSprite("assets/background1_mid.png");
	sprites.push_back(mg);

	// don't push foreground into sprites vector so we can control it's rendering to be last
	fg = new stillSprite("assets/background1_front.png");

	// call superclass constructor
	playState::init();

	// initialize variables
	this->enemySpawnCounter = 0.0;

	// Spawn in the big enemies
	for (int i = 0; i < 5; i++) {
		bigEnemy* temp = new bigEnemy();
		temp->setPos(rand() % 1800 + 100, 400 + rand() % 80 - 40);
		bigEnemies.push_back(temp);
	}

	// set initial player position
	this->mainPlayer->setPos(400, 300);

}

void level1::close() {
	playState::close();
}

// OVERRIDE the playstate event handler to take on player attacks
void level1::handleEvents(bool& running) {

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
			if (e.key.keysym.sym == SDLK_q) {
				mainPlayer->attack(enemies, bigEnemies);
			}
			if (e.key.keysym.sym == SDLK_w){
				mainPlayer->attack2(enemies, bigEnemies);
			}
		}
		// run an event handler on objects affected by player input
		mainPlayer->eventHandler(e);
	}
}

void level1::update() {

	playState::update();
	// make sure the player doesn't go out of bounds horizontally
	int curr_x = mainPlayer->getX(), curr_y = mainPlayer->getY();
	if (curr_x < MARGIN) {
		mainPlayer->setPos(MARGIN, curr_y);
	}
	if (curr_x > LEVEL_WIDTH-MARGIN) {
		mainPlayer->setPos(LEVEL_WIDTH-MARGIN, curr_y);
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
				// THIS MEANS THE PLAYER DIED
				std::cout << "DIED" << std::endl;
				// move on to the death menu
				changeState = true;
				nextState = new gameOver();
			}
		}
		// delete the enemy if it should be deleted
		if (enemies.at(i)->GET_DELETE()) {
			enemies.erase(enemies.begin()+i);
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
			bigEnemyFinal *temp = new bigEnemyFinal(bigEnemies.at(i)->getHealth(), bigEnemies.at(i)->getX()-10, bigEnemies.at(i)->getY()-10);
			bigEnemies.erase(bigEnemies.begin() + i);
			bigEnemies.push_back(temp);
		}
		// if the enemy has bloomed
		else if (bigEnemies.at(i)->getBloom()) {
			// THEN THE GAME IS OVER
			// THIS MEANS THE PLAYER DIED
			std::cout << "RIP" << std::endl;
			// move on to the death menu
			changeState = true;
			nextState = new gameOver();
		}
	}

	// update background parallaxing with respect to player position
	if (camera.x != 0 && camera.x != 2000-camera.w) {
		// only update background if background is moving (camera is moving)
		bg->setPos(-mainPlayer->getX() / 3, 0);
		mg->setPos(-mainPlayer->getX(), 0);
		fg->setPos(-mainPlayer->getX() * 2, 0);
	}

}

void level1::render(SDL_Surface* display) {
	playState::render(display);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->render(display, camera);
	}
	for (unsigned int i = 0; i < bigEnemies.size(); i++) {
		bigEnemies.at(i)->render(display, camera);
	}
	fg->render(display, camera);
}

void level1::handleEnemySpawn(float delta){

	// update the spawn timer
	enemySpawnCounter += delta;
	
	if (enemySpawnCounter >= SPAWN_TIME) {
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