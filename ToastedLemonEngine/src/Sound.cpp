#include "Sound.h"

Sound::Sound(const char* filePath) {
	SDL_LoadWAV(filePath, &wav_spec, &wav_buffer, &wav_length);
}

Sound::~Sound() {
	SDL_FreeWAV(wav_buffer);
}

void Sound::PlaySound(SDL_AudioDeviceID *device, int loop) {
	if (loop) {

	}
	else {

	}
}

void Sound::StopSound(SDL_AudioDeviceID* device) {

}
