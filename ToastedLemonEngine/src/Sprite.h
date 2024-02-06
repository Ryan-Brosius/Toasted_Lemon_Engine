#pragma once
#include "Game.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(const char* fileName);
	void draw(SDL_Texture* surface, int x, int y);
	void scale(int x_scale, int y_scale);

private:
	SDL_Surface* sprite;
	int width;
	int height;
	int hot_x;
	int hot_y;
	int scale_x;
	int scale_y;
	void rotation(double rotate, int* x, int* y);
};

