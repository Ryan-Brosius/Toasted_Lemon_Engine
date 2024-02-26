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

int Sound::PlaySound(int loop) {
	SDL_QueueAudio(audioDevice, wav_buffer, wav_length);
	SDL_PauseAudioDevice(audioDevice, 0);
	
	if (loop) {
		Uint32 sampleSize = SDL_AUDIO_BITSIZE(wav_spec.format) / 8;
		Uint32 sampleCount = wav_length / sampleSize;
		Uint32 sampleLen = 0;
		if (wav_spec.channels) {
			sampleLen = sampleCount / wav_spec.channels;
		}
		else {
			sampleLen = sampleCount;
		}

		return (double)sampleLen / (double)wav_spec.freq;;
	}
	else {
		return 0;
	}
}

void Sound::StopSound() {
	SDL_PauseAudioDevice(audioDevice, 1);
}
