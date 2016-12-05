#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class sprite {

public:

	sprite(std::string);
	virtual ~sprite();

	virtual int getX();
	virtual int getY();
	virtual void setPos(int, int);
	virtual void setCollisionRect(int, int);
	virtual SDL_Rect getCollisionRect();

	virtual void update(float);
	virtual void render(SDL_Surface*);

protected:

	int x, y;

	SDL_Rect blitRect;
	SDL_Rect collisionRect;

	SDL_Surface * img;

};