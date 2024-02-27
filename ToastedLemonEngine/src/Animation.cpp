#include "Animation.h"
#include "Game.h"
#include "Sprite.h"

extern Game* game;

Animation::Animation() 
{
	local_time = 0;
	sprite_sheet = nullptr;

	total_frames = 1;
	current_frame = 0;
	time_between_frames = 0;
	animating = true;
}

Animation::~Animation() {}

void Animation::init(const char* spritesheet, int frames, double time) 
{
	Sprite* sprite = new Sprite();
	sprite->init(spritesheet);
	sprite_sheet = sprite;

	total_frames = frames;
	time_between_frames = time;

	sprite->setSpriteSheet(frames);
}

void Animation::update() 
{
	if (animating && total_frames != 1)
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

void Animation::setAnimating(bool ani)
{
	animating = ani;
}

Sprite* Animation::getSprite()
{
	return sprite_sheet;
}

void Animation::draw(SDL_Texture* surface, int x, int y)
{
	sprite_sheet->draw(surface, x, y);
}