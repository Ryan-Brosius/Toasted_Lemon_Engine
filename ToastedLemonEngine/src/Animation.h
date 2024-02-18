#pragma once
#include "Sprite.h"

class Animation
{
public:
	Animation();
	~Animation();

	void init(Sprite* sprite_sheet, int total_frames, double time_between_frames);

	void update();

private:
	double local_time;
	Sprite* sprite_sheet;

	int total_frames;
	int current_frame;
	double time_between_frames;

	void determineFrame();
};

