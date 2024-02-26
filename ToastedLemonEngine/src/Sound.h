#pragma once
#include "Game.h"

class Sound {
public:
	Sound(const char* filePath);
	~Sound();
	void PlaySound(int loop);
	void StopSound();

private:
	SDL_AudioDeviceID audioDevice;
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;
};
