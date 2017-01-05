#include "level1.hh"

void level1::init() {

	// Add the background first so it always gets rendered first
	background = new sprite("assets/BG1.png");
	sprites.push_back(background);

	// call superclass constructor
	playState::init();

	// initialize variables
	this->enemySpawnCounter = 0.0;

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
				mainPlayer->attack(enemies);
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
			}
			else {
				std::cout << mainPlayer->getHealth() << std::endl;
			}
		}
		// delete the enemy if it should be deleted
		if (enemies.at(i)->GET_DELETE()) {
			enemies.erase(enemies.begin()+i);
		}
	}

}

void level1::render(SDL_Surface* display) {
	playState::render(display);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->render(display, camera);
	}
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