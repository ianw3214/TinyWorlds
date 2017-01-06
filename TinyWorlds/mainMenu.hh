#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "gameState.hh"
#include "level1.hh"
#include "sprite.hh"

struct menuItem {

	sprite * img;
	sprite * img_selected;
	menuItem * nextItem;
	menuItem * prevItem;
	int key;

};

class mainMenu : public gameState {

public:

	mainMenu();

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render(SDL_Surface*);

private:

	menuItem * selected, * first;
	sprite * background;

	void select();

};