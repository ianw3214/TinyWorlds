#pragma once

#include <vector>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "playState.hh"
#include "boss.hh"
#include "stillSprite.hh"
#include "gameOver.hh"
#include "cutScene.hh"
#include "bullet.hh"

constexpr int LEVEL_WIDTH_3 = 2000;

class last : public playState {

public:

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render(SDL_Surface*);

private:

	stillSprite * bg;
	stillSprite * black;
	float quitTimer;

	boss * finalBoss = new boss();
	std::vector<sprite*> topLevel;
	std::vector<bullet*> bullets;

	float attackTimer;

	bool GAME_OVER;
	void game_over(int);

};