#pragma once
#include "Sound.h"
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <iostream>

class Audio {
public:
	Audio();
	~Audio();

	void init();
	void Update();
	void PlayAudio(const char* fileName, int loop);
	void StopAudio(const char* fileName);

private:
	const char* audioPath = "Assets/Audio";
	SDL_AudioSpec audioSpec;
	std::map<std::string, Sound*> audioFiles;
	std::vector<std::string> loopFiles;
};
