#include "Audio.h"
#include "Sound.h"
#include <filesystem>
#include <iostream>
//namespace directory_iterator = std::filesystem::directory_iterator;

Audio::Audio() {
	audioDevice = SDL_OpenAudioDevice(
		nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE
	);

	//for (const auto& entry : directory_iterator(audioPath)) {
	//	audioFiles[entry];
	//}
}

Audio::~Audio() {
	SDL_CloseAudioDevice(audioDevice);
}

void Audio::PlayAudio(char* fileName, int loop) {
	audioFiles[fileName]->PlaySound(&audioDevice, loop);
}
