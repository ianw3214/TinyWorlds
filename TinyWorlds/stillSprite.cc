#include "stillSprite.hh"

void stillSprite::render(SDL_Surface * display, SDL_Rect camera) {
	SDL_Rect targetRect = { x, y, 0, 0 };
	if (SDL_BlitSurface(img, nullptr, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, ERROR: " << IMG_GetError() << std::endl;
	}
}