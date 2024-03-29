#include "Networking.h"
#include "Game.h"

NetworkClient::NetworkClient()
{
	return;
}

void NetworkClient::init()
{
	SDLNet_Init();
	socketSet = SDLNet_AllocSocketSet(1);
}

void NetworkClient::ConnectToHost(const char* pIP, int port)
{
	if (SDLNet_ResolveHost(&ip, pIP, port) == -1)
	{
		fprintf(stderr, "Error SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-1);
	}
	socket = SDLNet_TCP_Open(&ip);
	SDLNet_TCP_AddSocket(socketSet, socket);
}


void NetworkClient::CloseSocket()
{
	SDLNet_TCP_Close(socket);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_Quit();
}

void NetworkClient::Encode()
{
}

void NetworkClient::Decode(TCPsocket sender)
{
	int code;
	int UIDbuffer;
	int incomingUID;
	double xpos;
	double ypos;
	double animEnum;
	double animLocalTime;
	double animating;

	sscanf(incomingMessage, "%d", &code);

	switch (code)
	{
	case 0:
		sscanf(incomingMessage, "%d %d", &code, &UIDbuffer);
		UID = UIDbuffer;
		std::cout << "UID recieved: " << UID << "\n";
		break;
	case 1:
		sscanf(incomingMessage, "%d %d", &code, &UIDbuffer);
		game->createNetworkPlayer(UIDbuffer);
		std::cout << "PLAYER UID IN MAP: " << UIDbuffer << std::endl;
		break;
	case 2:
		sscanf(incomingMessage, "%d %d %lf %lf %lf %lf %lf", &code, &UIDbuffer, &xpos, &ypos, &animEnum, &animLocalTime, &animating);
		if (xpos != NULL && ypos != NULL)
		{
			game->moveNetPlayer(UIDbuffer, xpos, ypos);
		}
		game->setAnimNetPlayer(UIDbuffer, (int)animEnum, animLocalTime, (int)animating);
		break;
	}
}

void NetworkClient::Send()
{
	double* position = (double*)malloc(sizeof(double) * 2);
	double* anim = (double*)malloc(sizeof(double) * 3);

	game->GetPlayerPosition(position);
	game->GetPlayerAnim(anim);

	if (*position != NULL && *(position + 1) != NULL)
	{
		SDL_Delay(1);
		sprintf(message, "2 %d %f %f %f %f %f\n", UID, *position, *(position + 1), *anim, *(anim + 1), *(anim + 2));
		SDLNet_TCP_Send(socket, message, strlen(message) + 1);
	}

	free(position);
	free(anim);
}

void NetworkClient::Recieve()
{
	if (SDLNet_CheckSockets(socketSet, 0) && SDLNet_SocketReady(socket))
	{
		SDLNet_TCP_Recv(socket, incomingMessage, 1024);
		Decode(socket);
	}
}
