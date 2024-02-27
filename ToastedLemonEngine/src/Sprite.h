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
	void setRotation(double rot);
	double getRotation();
	void setSpriteSheet(int sprites);
	void setSheetOffset(int offset);

private:
	SDL_Surface* sprite;
	int sprite_width;
	int sprite_height;
	int width;
	int height;
	int hot_x;
	int hot_y;
	int scale_x;
	int scale_y;
	double rotation;
	int sheet_offset;
};

