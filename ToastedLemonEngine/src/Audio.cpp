#include "Audio.h"
#include "Sound.h"

Audio::Audio() {
	Audio::init();
}

Audio::~Audio() {
	for (const auto& item : audioFiles) {
		item.second->~Sound();
	}
	SDL_CloseAudioDevice(audioDevice);
}

void Audio::init() {
	audioDevice = SDL_OpenAudioDevice(
		nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE
	);

	for (const auto& entry : std::filesystem::directory_iterator(audioPath)) {
		audioFiles[entry.path().filename().string()] = new Sound(entry.path().string().c_str());
	}
}

void Audio::PlayAudio(const char* fileName, int loop) {
	audioFiles[fileName]->PlaySound(&audioDevice, loop);
}

void Audio::StopAudio(const char* fileName) {
	audioFiles[fileName]->StopSound(&audioDevice);
}
