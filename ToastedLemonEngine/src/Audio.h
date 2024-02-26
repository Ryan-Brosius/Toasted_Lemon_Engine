#pragma once
#include "Game.h"
#include "Sound.h"
#include <vector>
#include <string>
#include <filesystem>
#include <map>

class Audio {
public:
	Audio();
	~Audio();

	void PlayAudio(char* fileName, int loop);

private:
	const char* audioPath = "Assets/Audio";
	SDL_AudioSpec audioSpec;
	SDL_AudioDeviceID audioDevice;
	map<char*, Sound*> audioFiles;
};
