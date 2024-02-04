#pragma once
#include "Game.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(const char* fileName);
	void draw(SDL_Texture* surface, int x, int y);

private:
	SDL_Surface* sprite;
	int width;
	int height;
	int hot_x;
	int hot_y;
};

