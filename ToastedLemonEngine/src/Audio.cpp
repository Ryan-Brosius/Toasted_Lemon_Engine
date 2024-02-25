#include "Audio.h"

Audio::Audio() {
	audioPath = "Assets/Audio";
	//if (SDL_LoadWAV("test.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
	//	fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
	//}
	//else {
	//	/* Do stuff with the WAV data, and then... */
	//	SDL_FreeWAV(wav_buffer);
	//}

}

Audio::~Audio() {

}

void Audio::init() {

}

void Audio::PlaySound(const char* fileName) {
	
}
