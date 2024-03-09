#include "TilesheetMap.h"
#include "Sprite.h"

int demo[20][17] = {
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
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
};

TilesheetMap::TilesheetMap()
{
	int tileNum = 0;
	for (const auto& entry : std::filesystem::directory_iterator(audioPath)) {
		mapTiles[tileNum] = new Sprite();
		mapTiles[tileNum]->init(entry.path().string().c_str());
		mapTiles[tileNum]->scale(3, 3);
		tileNum++;
	}

	LoadMap((int*)demo, 13, 17);
}

TilesheetMap::~TilesheetMap() {}

void TilesheetMap::LoadMap(int* arr, int height, int width)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			map[row][col] = *(arr + col + (width * row));
		}
	}
}

void TilesheetMap::DrawMap(SDL_Texture* framebuffer, int camera_pos_x, int camera_pos_y)
{
	int type = 0;
	int width = 48;
	int height = 48;

	camera_pos_x = SDL_max(camera_pos_x, 0);
	camera_pos_y = SDL_max(camera_pos_y, 0);

	int xpos_offset = -1 * camera_pos_x;
	int ypos_offset = -1 * camera_pos_y;

	int row = camera_pos_y / height;
	int maxRow = 1 + row + HEIGHT / height;

	int col = camera_pos_x / width;
	int maxCol = 1 + col + WIDTH / width;


	for (int i = row; i < maxRow; i++)
	{
		for (int j = col; j < maxCol; j++)
		{
			int xpos = j * width;
			int ypos = i * height;
			type = map[i][j];
			if (mapTiles[type] != nullptr)
				mapTiles[type]->draw(framebuffer, xpos + xpos_offset, ypos + ypos_offset);
		}
	}
}

void TilesheetMap::DrawMap(SDL_Texture* framebuffer)
{
	TilesheetMap::DrawMap(framebuffer, 0, 0);
}