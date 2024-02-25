#pragma once
#include "../Game.h"
#include "Sound.h"
#include <list>
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
	list<Uint8> audioFiles;
	Uint8 audioFile;
	string audioPath;
};