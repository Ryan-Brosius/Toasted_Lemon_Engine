#include "Sound.h"

Sound::Sound(const char* filePath) {
	// Loads a WAV file given the file path and opens the default audio device
	if (SDL_LoadWAV(filePath, &wav_spec, &wav_buffer, &wav_length) == nullptr) {
		std::cerr << "Could not Load Audio File: " << SDL_GetError() << std::endl;
	}
	audioDevice = SDL_OpenAudioDevice(
		nullptr, 0, &wav_spec, nullptr, 0
	);

	// Initalizes playTime and audioLength
	playTime = 0;
	audioLength = Sound::GetPlayTime();
}

Sound::~Sound() {
	// Frees the loaded WAV file and closes the audio device
	SDL_FreeWAV(wav_buffer);
	SDL_CloseAudioDevice(audioDevice);
}

void Sound::Update() {
	// Adds the time and determines whether the audio should be replayed
	playTime += game->deltaTime();
	if (Sound::PlayTimeReached()) {
		Sound::StopSound();
		Sound::PlaySound();
		playTime = 0;
	}
}

void Sound::PlaySound() {
	// Plays the audio of the loaded WAV file
	SDL_QueueAudio(audioDevice, wav_buffer, wav_length);
	SDL_PauseAudioDevice(audioDevice, 0);
}

void Sound::StopSound() {
	// Stops the audio of the loaded WAV file
	SDL_PauseAudioDevice(audioDevice, 1);
	SDL_ClearQueuedAudio(audioDevice);
}

int Sound::GetPlayTime() {
	// Returns the loaded WAV file's length in seconds
	Uint32 sampleSize = SDL_AUDIO_BITSIZE(wav_spec.format) / 8;
	Uint32 sampleCount = wav_length / sampleSize;
	Uint32 sampleLen = 0;
	if (wav_spec.channels) {
		sampleLen = sampleCount / wav_spec.channels;
	}
	else {
		sampleLen = sampleCount;
	}

	return (double)sampleLen / (double)wav_spec.freq;
}

bool Sound::PlayTimeReached() {
	return playTime >= audioLength;
}
