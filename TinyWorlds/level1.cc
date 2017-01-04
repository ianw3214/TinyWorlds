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

void level1::handleEvents(bool& quit) {
	playState::handleEvents(quit);
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
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->update(delta, mainPlayer->getX(), mainPlayer->getY());
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
		test->setPos(rand() % 1800 + 100, rand() % 250 + 300);
		enemies.push_back(test);
		// reset the spawn counter
		enemySpawnCounter = 0.0;
	}

}