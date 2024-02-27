#include "TilesheetMap.h"
#include "Sprite.h"

int demo[13][17] = {
	{ 0, 2, 0, 0, 0, 0, 0,12, 8,13, 1, 0, 3, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 1,12, 8,13, 0, 0, 0, 0, 2, 0, 0},
	{ 0, 0, 6, 7, 0, 0, 0,12, 8,13, 3, 0, 0, 6, 7, 0, 1},
	{ 0, 0, 4, 5, 2, 0, 0,12, 8,13, 0, 0, 1, 4, 5, 0, 0},
	{ 0, 0, 0, 2, 0, 3, 0,12, 8,13, 0, 2, 0, 0, 0, 3, 0},
	{ 0, 0, 0, 0, 0, 0, 3,12, 8,13, 0, 0, 0, 0, 0, 0, 0},
	{15,14,14,14,14,14,14, 8, 8, 8,14,14,14,14,14,14,16},
	{12, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
	{10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,11},
	{ 1, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 2, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{ 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
};

TilesheetMap::TilesheetMap()
{

	//Sprites for rock
	tm_rock_bottom_left->init("Assets/Sprites/Tilesprites/tm_rock_bottom_left.bmp");
	tm_rock_bottom_left->scale(3, 3);
	tm_rock_bottom_right->init("Assets/Sprites/Tilesprites/tm_rock_bottom_right.bmp");
	tm_rock_bottom_right->scale(3, 3);
	tm_rock_top_left->init("Assets/Sprites/Tilesprites/tm_rock_top_left.bmp");
	tm_rock_top_left->scale(3, 3);
	tm_rock_top_right->init("Assets/Sprites/Tilesprites/tm_rock_top_right.bmp");
	tm_rock_top_right->scale(3, 3);

	//Sprites for dark grass
	tm_dark_grass_full->init("Assets/Sprites/Tilesprites/tm_dark_grass_full.bmp");
	tm_dark_grass_full->scale(3, 3);
	tm_dark_grass_bottom->init("Assets/Sprites/Tilesprites/tm_dark_grass_bottom.bmp");
	tm_dark_grass_bottom->scale(3, 3);
	tm_dark_grass_bottom_left->init("Assets/Sprites/Tilesprites/tm_dark_grass_bottom_left.bmp");
	tm_dark_grass_bottom_left->scale(3, 3);
	tm_dark_grass_bottom_right->init("Assets/Sprites/Tilesprites/tm_dark_grass_bottom_right.bmp");
	tm_dark_grass_bottom_right->scale(3, 3);
	tm_dark_grass_left->init("Assets/Sprites/Tilesprites/tm_dark_grass_left.bmp");
	tm_dark_grass_left->scale(3, 3);
	tm_dark_grass_right->init("Assets/Sprites/Tilesprites/tm_dark_grass_right.bmp");
	tm_dark_grass_right->scale(3, 3);
	tm_dark_grass_top->init("Assets/Sprites/Tilesprites/tm_dark_grass_top.bmp");
	tm_dark_grass_top->scale(3, 3);
	tm_dark_grass_top_left->init("Assets/Sprites/Tilesprites/tm_dark_grass_top_left.bmp");
	tm_dark_grass_top_left->scale(3, 3);
	tm_dark_grass_top_right->init("Assets/Sprites/Tilesprites/tm_dark_grass_top_right.bmp");
	tm_dark_grass_top_right->scale(3, 3);

	//Green grass :)
	tm_grass_green->init("Assets/Sprites/Tilesprites/tm_grass_green.bmp");
	tm_grass_green->scale(3, 3);
	tm_grass_green_flower1->init("Assets/Sprites/Tilesprites/tm_grass_green_flower1.bmp");
	tm_grass_green_flower1->scale(3, 3);
	tm_grass_green_flower2->init("Assets/Sprites/Tilesprites/tm_grass_green_flower2.bmp");
	tm_grass_green_flower2->scale(3, 3);
	tm_grass_green_grass->init("Assets/Sprites/Tilesprites/tm_grass_green_grass.bmp");
	tm_grass_green_grass->scale(3, 3);

	LoadMap(demo);
}

TilesheetMap::~TilesheetMap() {}

void TilesheetMap::LoadMap(int arr[13][17]) 
{
	for (int row = 0; row < 13; row++)
	{
		for (int col = 0; col < 17; col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

void TilesheetMap::DrawMap(SDL_Texture* framebuffer)
{
	int type = 0;
	int width = 48;
	int height = 48;
	
	for (int row = 0; row < 13; row++)
	{
		for (int col = 0; col < 17; col++)
		{
			int xpos = col * width;
			int ypos = row * height;

			type = map[row][col];

			switch (type)
			{
			case 0:
				tm_grass_green->draw(framebuffer, xpos, ypos);
				break;
			case 1:
				tm_grass_green_flower1->draw(framebuffer, xpos, ypos);
				break;
			case 2:
				tm_grass_green_flower2->draw(framebuffer, xpos, ypos);
				break;
			case 3:
				tm_grass_green_grass->draw(framebuffer, xpos, ypos);
				break;
			case 4:
				tm_rock_bottom_left->draw(framebuffer, xpos, ypos);
				break;
			case 5:
				tm_rock_bottom_right->draw(framebuffer, xpos, ypos);
				break;
			case 6:
				tm_rock_top_left->draw(framebuffer, xpos, ypos);
				break;
			case 7:
				tm_rock_top_right->draw(framebuffer, xpos, ypos);
				break;
			case 8:
				tm_dark_grass_full->draw(framebuffer, xpos, ypos);
				break;
			case 9:
				tm_dark_grass_bottom->draw(framebuffer, xpos, ypos);
				break;
			case 10:
				tm_dark_grass_bottom_left->draw(framebuffer, xpos, ypos);
				break;
			case 11:
				tm_dark_grass_bottom_right->draw(framebuffer, xpos, ypos);
				break;
			case 12:
				tm_dark_grass_left->draw(framebuffer, xpos, ypos);
				break;
			case 13:
				tm_dark_grass_right->draw(framebuffer, xpos, ypos);
				break;
			case 14:
				tm_dark_grass_top->draw(framebuffer, xpos, ypos);
				break;
			case 15:
				tm_dark_grass_top_left->draw(framebuffer, xpos, ypos);
				break;
			case 16:
				tm_dark_grass_top_right->draw(framebuffer, xpos, ypos);
				break;
			default:
				break;
			}
		}
	}
}