#include "Sound.h"

Sound::Sound(const char* filePath) {
	if (SDL_LoadWAV(filePath, &wav_spec, &wav_buffer, &wav_length) == nullptr) {
		std::cerr << "Could not Load Audio File: " << SDL_GetError() << std::endl;
	}
	audioDevice = SDL_OpenAudioDevice(
		nullptr, 0, &wav_spec, nullptr, 0
	);
}

Sound::~Sound() {
	SDL_FreeWAV(wav_buffer);
	SDL_CloseAudioDevice(audioDevice);
}

void Sound::PlaySound(int loop) {
	SDL_QueueAudio(audioDevice, wav_buffer, wav_length);
	SDL_PauseAudioDevice(audioDevice, 0); 
}

void Sound::StopSound() {
	SDL_PauseAudioDevice(audioDevice, 1);
}
