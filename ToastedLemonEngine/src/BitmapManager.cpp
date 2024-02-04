#include "BitmapManager.h"

SDL_Surface* BitmapManager::LoadBitmap(const char* fileName)
{
	SDL_Surface* bitmapSurface = SDL_LoadBMP(fileName);
	if (!bitmapSurface) {
		std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
	}

	return bitmapSurface;

}