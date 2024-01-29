#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void initialize_environment(void) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(
		window,
		-1,
		0);
}

void render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	initialize_environment();

	while (1) {
		render();

		SDL_Delay(1);
	}

	return 0;
}