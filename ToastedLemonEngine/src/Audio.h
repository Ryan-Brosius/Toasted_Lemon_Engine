#pragma once
#include "Game.h"
#include "Sound.h"
#include <vector>
#include <string>
#include <filesystem>
#include <map>
#include <string>
#include <iostream>

class Audio {
public:
	Audio();
	~Audio();

	void init();
	int PlayAudio(const char* fileName, int loop);
	void StopAudio(const char* fileName);

private:
	const char* audioPath = "Assets/Audio";
	SDL_AudioSpec audioSpec;
	std::map<std::string, Sound*> audioFiles;
};
