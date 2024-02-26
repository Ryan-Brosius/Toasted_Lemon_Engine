#include "Audio.h"
#include "Sound.h"

Audio::Audio() {
	Audio::init();
}

Audio::~Audio() {
	for (const auto& item : audioFiles) {
		item.second->~Sound();
	}
}

void Audio::init() {
	for (const auto& entry : std::filesystem::directory_iterator(audioPath)) {
		audioFiles[entry.path().filename().string()] = new Sound(entry.path().string().c_str());
	}
}

int Audio::PlayAudio(const char* fileName, int loop) {
	return audioFiles[fileName]->PlaySound(loop);
}

void Audio::StopAudio(const char* fileName) {
	audioFiles[fileName]->StopSound();
}
