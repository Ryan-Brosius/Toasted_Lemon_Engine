#pragma once
#include "Game.h"
#include <vector>

extern Game* game;

class Sound {
public:
	Sound(const char* filePath);
	~Sound();
	void Update();
	void PlaySound();
	void StopSound();
	int GetPlayTime();

private:
	bool PlayTimeReached();

	SDL_AudioDeviceID audioDevice;
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8* wav_buffer;

	double playTime;  // The current timer - if looping is enabled
	double audioLength;  // The loaded WAV file's length in seconds
};
