#pragma once
#include "Game.h"
#include <vector>

class Sound {
public:
	Sound(const char* filePath);
	~Sound();
	int PlaySound(int loop);
	void StopSound();

private:
	SDL_AudioDeviceID audioDevice;
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;
};
