#pragma once
#include "Game.h"

class Sound {
public:
	Sound(const char* filePath);
	~Sound();
	void PlaySound(SDL_AudioDeviceID *device, int loop);
	void StopSound(SDL_AudioDeviceID* device);

private:
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;
};
