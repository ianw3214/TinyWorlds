#pragma once

#include "engine.hh"

class gameState {

public:

	gameState();

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void handleEvents(engine * game) = 0;
	virtual void update(engine * game) = 0;
	virtual void render(engine * game) = 0;

};