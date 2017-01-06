#include "mainMenu.hh"

mainMenu::mainMenu() {

}

void mainMenu::init() {

	// initialize sprites
	this->background = new sprite("assets/menu_bg.png");

	// initialize menu items

	// PLAY GAME BUTTON
	menuItem * item1 = new menuItem();
	item1->img = new sprite("assets/menu1.png", 350, 200);
	item1->img_selected = new sprite("assets/menu1_select.png", 350, 200);
	item1->key = 0;
	item1->prevItem = nullptr;
	this->selected = item1;
	this->first = item1;

	// OPTIONS BUTTON
	menuItem * item2 = new menuItem();
	item2->img = new sprite("assets/menu2.png", 350, 260);
	item2->img_selected = new sprite("assets/menu2_select.png", 350, 260);
	item2->key = 1;
	item2->prevItem = item1;
	item1->nextItem = item2;

	// QUIT BUTTON
	menuItem * item3 = new menuItem();
	item3->img = new sprite("assets/menu3.png", 350, 320);
	item3->img_selected = new sprite("assets/menu3_select.png", 350, 320);
	item3->key = 2;
	item3->prevItem = item2;
	item2->nextItem = item3;
	item3->nextItem = nullptr;

}

void mainMenu::close() {

}

void mainMenu::handleEvents(bool& running) {

	SDL_Event e;

	// get the SDL events
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
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
		nextState = new level1();
		changeState = true;
	} break;
	case 1: {	// OPTIONS
		std::cout << "TEST" << std::endl;
	} break;
	case 2: {	// QUIT
		changeState = true;
		nextState = nullptr;
	} break;
	}

}