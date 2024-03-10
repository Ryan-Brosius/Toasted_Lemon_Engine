#pragma once
#include "Sprite.h"

class Animation
{
public:
	Animation();
	~Animation();

	void init(const char* sprite_sheet, int total_frames, double time_between_frames);

	void update();

	void setAnimating(bool animating);

	Sprite* getSprite();

	void draw(SDL_Texture* surface, int x, int y);

	double getLocalTime();
	void setLocalTime(double time);

	bool animating;

private:
	double local_time;
	Sprite* sprite_sheet;

	int total_frames;
	int current_frame;
	double time_between_frames;

	void determineFrame();
};

