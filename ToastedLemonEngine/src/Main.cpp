#include <stdio.h>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int fps = 120;
	const int frameDelay = 1000 / fps;
	
	Uint32 frameStart = 0;
	Uint32 previousRender = 0;

	game = new Game();
	game->init(NULL, WIDTH, HEIGHT, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handelEvents();		//Will be used to handle input in the future
		game->update();

		if (frameDelay <= (frameStart - previousRender)) {
			game->render();
			previousRender = SDL_GetTicks();
		}

		SDL_Delay(1);
	}

	game->clean();

	return 0;
}