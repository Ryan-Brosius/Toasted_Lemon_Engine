#include "Audio.h"
#include "Sound.h"

Audio::Audio() {
	Audio::init();
}

Audio::~Audio() {
	// Frees all the Sound objects
	for (const auto& item : audioFiles) {
		item.second->~Sound();
	}
}

void Audio::init() {
	// Initializes all Sound objects for all files in Assets/Audio
	for (const auto& entry : std::filesystem::directory_iterator(audioPath)) {
		audioFiles[entry.path().filename().string()] = new Sound(entry.path().string().c_str());
	}
}

void Audio::Update() {
	// Checks if there are files to loop and if there is, updates the loop Sound objects
	if (!loopFiles.empty()) {
		for (const auto& entry : loopFiles) {
			audioFiles[entry]->Update();
		}
	}
}

void Audio::PlayAudio(const char* fileName, int loop) {
	// Plays the audio for the given file name and sets a Sound to loop if flag - loop > 0
	if (loop) loopFiles.insert(loopFiles.end(), fileName);
	audioFiles[fileName]->PlaySound();
}

void Audio::StopAudio(const char* fileName) {
	// Stops the audio for the given file name
	audioFiles[fileName]->StopSound();
}
