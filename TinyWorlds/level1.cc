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
		test->setPos(rand() % 1800 + 100, rand() % 250 + 300);
		enemies.push_back(test);
		// reset the spawn counter
		enemySpawnCounter = 0.0;
	}

}