#include <stdio.h>
#include "Game.h"
#include "Networking.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps;
	
	Uint32 frameStart = 0;
	Uint32 previousRender = 0;

	game = new Game();
	game->init(NULL, WIDTH, HEIGHT, false);

	NetworkServer server = NetworkServer(4);
	server.init();

	NetworkClient client = NetworkClient();
	client.init();
	client.ConnectToHost(server.GetHostName(), 8099);

	server.CheckConnections();

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handelEvents();
		game->update();

		if (frameDelay <= (frameStart - previousRender)) {
			game->render();
			previousRender = SDL_GetTicks();
		}

		server.SendTest();
		client.RecvTest();

		SDL_Delay(1);
	}

	game->clean();
	server.CloseSocket();

	return 0;
}