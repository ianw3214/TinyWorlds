#include "last.hh"

void last::init() {

	// call superclass constructor
	playState::init();

	// set initial player position
	this->mainPlayer->setPos(1000, 300);

	finalBoss = new boss();
	attackTimer = 0.0;

	bg = new stillSprite("assets/background3.png");
	bg->setPos(0, 0);
	quitTimer = 10.0;

	// load the music
	Mix_Chunk * wav = Mix_LoadWAV("music/track3.wav");
	if (wav == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
	if (Mix_PlayChannel(2, wav, -1) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}

}

void last::close() {
	playState::close();
}

// OVERRIDE the playstate event handler to take on player attacks
void last::handleEvents(bool& running) {

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
				mainPlayer->attack1(finalBoss);
			}
			if (e.key.keysym.sym == SDLK_w && !GAME_OVER) {
				mainPlayer->attack2(finalBoss);
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

void last::update() {

	if (finalBoss->getDead()) {
		quitTimer -= delta;
		if (quitTimer <= 0.0) {
			game_over(1);
		}
	}

	// update the bosses attack
	if (attackTimer <= 0.0 && !finalBoss->getDead()) {
		attackTimer = 3.5;
		for (int i = 0; i < 8; i++) {
			bullet * temp = new bullet(i, finalBoss->getX(), finalBoss->getY());
			bullets.push_back(temp);
		}
	}
	else {
		attackTimer -= delta;
	}

	// update everything only if the game is still running
	if (!GAME_OVER) {

		playState::update();
		finalBoss->update(delta);
		// make sure the player doesn't go out of bounds horizontally
		int curr_x = mainPlayer->getX(), curr_y = mainPlayer->getY();
		if (curr_x < MARGIN - 40) {
			mainPlayer->setPos(MARGIN - 40, curr_y);
		}
		if (curr_x > LEVEL_WIDTH_3 - MARGIN) {
			mainPlayer->setPos(LEVEL_WIDTH_3 - MARGIN, curr_y);
		}
		// damage the player if he hits a bullet
		for (int i = 0; i < bullets.size(); i++) {
			bullets.at(i)->update(delta);
			if (SDL_HasIntersection(&bullets.at(i)->getCollisionRect(), &mainPlayer->getCollisionRect())) {
				if (!mainPlayer->takeDamage(1)) {
					// if the function returns false, then the player has died
					game_over(0);
				}
			}
		}
		// damage the player if he hits the boss
		if (SDL_HasIntersection(&finalBoss->getCollisionRect(), &mainPlayer->getCollisionRect()) && !finalBoss->getDead()) {
			if (!mainPlayer->takeDamage(1)) {
				// if the function returns false, then the player has died
				game_over(0);
			}
		}

	}
	else {
		mainPlayer->update(delta);
	}

}

void last::render(SDL_Surface* display) {

	bg->render(display, camera);
	playState::render(display);
	// render hearts to represent player health
	for (unsigned int i = 0; i < mainPlayer->getHealth(); i++) {
		stillSprite * temp = new stillSprite("assets/heart.png");
		temp->setPos(20 + i * 40, 20);
		temp->render(display, camera);
	}
	finalBoss->render(display, camera);
	mainPlayer->render(display, camera);

	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->render(display, camera);
	}

	// render the top level content
	for (unsigned int i = 0; i < topLevel.size(); i++) {
		topLevel.at(i)->render(display, camera);
	}

}

// function that handles dealing with game over
void last::game_over(int key) {
	// Takes different keys to represent different game over states
	// 0 -> GAME LOST BY PLAYER DEATH
	// 1 -> GAME WON

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

		// The player won the game
		mainPlayer->stopMovement();
		GAME_OVER = true;

		// move to a cutscene and then level 2
		cutScene * last = new cutScene("assets/cutscenes/credits2.png", nullptr, mute, wave);
		cutScene * scene = new cutScene("assets/cutscenes/credits1.png", last, mute, wave);
		nextState = scene;
		changeState = true;

		// close the music
		Mix_FadeOutMusic(10);
		Mix_FreeChunk(wave);
		// load the music
		wave = Mix_LoadWAV("music/track1.wav");
		if (wave == nullptr) {
			std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		}
		if (Mix_PlayChannel(2, wave, -1) == -1) {
			std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
		}

	}

}