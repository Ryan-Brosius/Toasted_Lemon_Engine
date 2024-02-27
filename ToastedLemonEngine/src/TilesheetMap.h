#pragma once
#include "Sprite.h"

class TilesheetMap
{
public:
	TilesheetMap();
	~TilesheetMap();

	void LoadMap(int arr[13][17]);
	void DrawMap(SDL_Texture* framebuffer);

private:

	int sprite_size;

	//Sprites for rock
	Sprite* tm_rock_bottom_left = new Sprite();
	Sprite* tm_rock_bottom_right = new Sprite();
	Sprite* tm_rock_top_left = new Sprite();
	Sprite* tm_rock_top_right = new Sprite();

	//Sprites for dark grass
	Sprite* tm_dark_grass_full = new Sprite();
	Sprite* tm_dark_grass_bottom = new Sprite();
	Sprite* tm_dark_grass_bottom_left = new Sprite();
	Sprite* tm_dark_grass_bottom_right = new Sprite();
	Sprite* tm_dark_grass_left = new Sprite(); 
	Sprite* tm_dark_grass_right = new Sprite(); 
	Sprite* tm_dark_grass_top = new Sprite();
	Sprite* tm_dark_grass_top_left = new Sprite();
	Sprite* tm_dark_grass_top_right = new Sprite();

	//Green grass :)
	Sprite* tm_grass_green = new Sprite();
	Sprite* tm_grass_green_flower1 = new Sprite();
	Sprite* tm_grass_green_flower2 = new Sprite();
	Sprite* tm_grass_green_grass = new Sprite();

	int map[20][25];
};

