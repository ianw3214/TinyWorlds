#include "sprite.hh"

// DEFAULT CONSTRUCTOR
sprite::sprite(std::string path) {

	// LOAD THE IMAGE FROM THE PATH TO THE SPRITE SURFACE
	img = IMG_Load(path.c_str());
	if (!img) {
		std::cout << "Failed to load image: " << path << ", SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

}

// DESTRUCTOR
sprite::~sprite() {

}

// GETTER/SETTER METHODS
int sprite::getX() { return this->x; }
int sprite::getY() { return this->y; }
void sprite::setPos(int x, int y) { this->x = x, this->y = y; }
void sprite::setCollisionRect(int w, int h) { this->collisionRect = { x, y, w, h }; }
SDL_Rect sprite::getCollisionRect() { return this->collisionRect; }

// EMPTY UPDATE FUNCTION FOR DEFAULT SPRITE
void sprite::update(float delta) {

}

void sprite::render(SDL_Surface * display) {

	if (SDL_BlitSurface(img, nullptr, display, nullptr) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}

}