#pragma once
#include "Sprite.h"
#include <string>
#include <filesystem>
#include <map>
#include <string>
#include <iostream>

class TilesheetMap
{
public:
	TilesheetMap();
	~TilesheetMap();

	void LoadMap(int* arr, int width, int height);
	void DrawMap(SDL_Texture* framebuffer, int camera_pos_x, int camera_pos_y);
	void DrawMap(SDL_Texture* framebuffer);

private:

	int sprite_size;
	int map[100][100];

	const char* audioPath = "Assets/Sprites/Tilesprites";
	std::map<int, Sprite*> mapTiles;
};

