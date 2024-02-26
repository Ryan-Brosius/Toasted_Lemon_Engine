#pragma once
#include "Game.h"
#include "Sound.h"
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

class Audio {
public:
	Audio();
	~Audio();

	void init();
	void PlaySound(const char* fileName);

private:
	vector<Sound> audioFiles;
	Uint8 audioFile;
	string audioPath;
};
