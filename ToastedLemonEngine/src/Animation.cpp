#include "Animation.h"
#include "Game.h"

extern Game* game;

Animation::Animation() 
{
	double local_time = 0;
	Sprite* sprite_sheet = nullptr;

	int total_frames = 1;
	int current_frame = 0;
	double time_between_frames = 0;
}

Animation::~Animation() {}

void Animation::init(Sprite* s, int frames, double time) 
{
	sprite_sheet = s;
	total_frames = frames;
	time_between_frames = time;

	s->setSpriteSheet(frames);
}

void Animation::update() 
{
	Animation::determineFrame();
}

void Animation::determineFrame()
{
	if (local_time > total_frames * time_between_frames)
		local_time -= total_frames * time_between_frames;

	current_frame = (int)(local_time / time_between_frames);

	sprite_sheet->setSheetOffset(current_frame);

	local_time += game->deltaTime();
}