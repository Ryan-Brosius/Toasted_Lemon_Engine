#define _CRT_SECURE_NO_WARNINGS //just so the compiler wont be a pain in the ass and raise an error just for using sscanf

#include <stdio.h>
#include "Game.h"
#include "Networking.h"

#include <iostream>
#include <filesystem>

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int fps = 120;
	const int frameDelay = 1000 / fps;
	
	Uint32 frameStart = 0;
	Uint32 previousRender = 0;

	bool isServer;

	//sets if instance is a server or not
	isServer = false;

	game = new Game();
	game->init(NULL, WIDTH, HEIGHT, false);	

	NetworkClient client = NetworkClient(*game);
	NetworkServer server = NetworkServer(4);

	if (isServer)
	{
		std::cout << "Starting as server\n";
		server.init();
		server.GetHostName();
	}

	std::cout << "Starting client\n";
	client.init();
	client.ConnectToHost("LAPTOP-KPQO6LSU", 8099);
	
	

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handelEvents();		//Will be used to handle input in the future
		game->update();

		if (frameDelay <= (frameStart - previousRender)) {
			game->render();
			previousRender = SDL_GetTicks();
		}

		if (isServer)
		{
			server.CheckConnections();
			server.Recieve();
		}
		
		client.Recieve();
		client.Send();

		SDL_Delay(1);
	}

	game->clean();
	//server.CloseSocket();

	return 0;
}
