#include "mainMenu.hh"

mainMenu::mainMenu() {

}

void mainMenu::init() {

	// initialize sprites
	this->background = new sprite("assets/main_menu/menu_bg.png");

	// initialize menu items

	// PLAY GAME BUTTON
	menuItem * item1 = new menuItem();
	item1->img = new sprite("assets/main_menu/menu1.png", 800, 400);
	item1->img_selected = new sprite("assets/main_menu/menu1_select.png", 800, 400);
	item1->key = 0;
	item1->prevItem = nullptr;
	this->selected = item1;
	this->first = item1;

	// OPTIONS BUTTON
	menuItem * item2 = new menuItem();
	item2->img = new sprite("assets/main_menu/menu2.png", 800, 460);
	item2->img_selected = new sprite("assets/main_menu/menu2_select.png", 800, 460);
	item2->key = 1;
	item2->prevItem = item1;
	item1->nextItem = item2;

	// QUIT BUTTON
	menuItem * item3 = new menuItem();
	item3->img = new sprite("assets/main_menu/menu3.png", 800, 520);
	item3->img_selected = new sprite("assets/main_menu/menu3_select.png", 800, 520);
	item3->key = 2;
	item3->prevItem = item2;
	item2->nextItem = item3;
	item3->nextItem = nullptr;

	// audio intialization
	wave = Mix_LoadWAV("music/track1.wav");
	if (wave == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
	if (Mix_PlayChannel(2, wave, -1) == -1) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
	}
	else {
		Mix_Volume(2, 64);
	}
	mute = false;

}

void mainMenu::close() {

}

void mainMenu::handleEvents(bool& running) {

	SDL_Event e;

	// get the SDL events
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			playSound();
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE: {
				running = false;
			} break;
			case SDLK_UP: {
				if (selected->prevItem != nullptr) {
					selected = selected->prevItem;
				}
			} break;
			case SDLK_DOWN: {
				if (selected->nextItem != nullptr) {
					selected = selected->nextItem;
				}
			} break;
			case SDLK_SPACE:
			case SDLK_RETURN: {
				select();
			} break;
			}
		}
	}

}

void mainMenu::update() {

}

void mainMenu::render(SDL_Surface* display) {

	// Render the menu background
	background->render(display, {});

	// Render the menu items
	menuItem * curr = first;

	while (curr != nullptr) {
		// determine which type of text to display
		if (selected == curr) {
			curr->img_selected->render(display, {});
		}
		else {
			curr->img->render(display, {});
		}
		// advance to the next menu item
		curr = curr->nextItem;
	}

}

// FUNCTION CALL WHEN MENU SHOULD CHANGE TO NEXT STATE
void mainMenu::select() {

	switch(selected->key){
	case 0: {	// PLAY GAME
		level1 * play  = new level1();
		cutScene * CS_1 = new cutScene("assets/cutscenes/cs_1.png", play, mute, wave);
		cutScene * instructions = new cutScene("assets/cutscenes/instructions.png", CS_1, mute, wave);
		nextState = instructions;
		changeState = true;

	} break;
	case 1: {	// OPTIONS
		if (mute) {
			mute = false;
			Mix_Volume(2, 64);
		}
		else {
			mute = true;
			Mix_Volume(2, 0);
		}
	} break;
	case 2: {	// QUIT
		changeState = true;
		nextState = nullptr;
	} break;
	}

}

void mainMenu::playSound() {

	// SDL_Mixer variable to hold the music file
	Mix_Chunk *tempWave = Mix_LoadWAV("music/menu.wav");
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