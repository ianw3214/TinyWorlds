#pragma once

#include <vector>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "playState.hh"
#include "enemy.hh"
#include "bigEnemy.hh"
#include "bigEnemyFinal.hh"
#include "stillSprite.hh"
#include "gameOver.hh"

constexpr int LEVEL_WIDTH = 2000;
constexpr float SPAWN_TIME = 1.0;

class level1 : public playState {

public:

	void init();
	void close();

	void handleEvents(bool&);
	void update();
	void render(SDL_Surface*);

	void handleEnemySpawn(float);

private:

	float enemySpawnCounter;
	std::vector<enemy*> enemies;
	std::vector<bigEnemy*> bigEnemies;

	// 3 different sprites to handle parallaxing/backgrounds
	stillSprite * bg, * mg, * fg;

};