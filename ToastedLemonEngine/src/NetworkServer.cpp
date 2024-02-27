#include "Networking.h"

NetworkServer::NetworkServer(int maxCon)
{
	next_ind = 0;
	/*TCPsocket server_socket;
	TCPsocket client;
	IPaddress ip;
	int maxConnections;
	SDLNet_SocketSet clientSocketSet;
	int currentCon;*/

	maxConnections = maxCon;
}

void NetworkServer::init()
{
	currentCon = 0;

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "Error SDL_Init: %sn", SDL_GetError());
		exit(-1);
	}

	if (SDLNet_Init() == -1)
	{
		fprintf(stderr, "Error SDLNet_Init: %sn", SDLNet_GetError());
	}

	if (SDLNet_ResolveHost(&ip, NULL, 8099) == -1)
	{
		fprintf(stderr, "Error SDLnet_ResolveHost: %sn", SDLNet_GetError());
		exit(-1);
	}

	server_socket = SDLNet_TCP_Open(&ip);
	if (server_socket == NULL)
	{
		fprintf(stderr, "Error SDLNet_TCP_Open: %sn", SDLNet_GetError());
		exit(-1);
	}

	clientSocketSet = SDLNet_AllocSocketSet(maxConnections);
	if (clientSocketSet == NULL)
	{
		fprintf(stderr, "Error SDLNet_AllocSocketSet: %sn", SDLNet_GetError());
		exit(-1);
	}
}

const char* NetworkServer::GetHostName()
{
	return SDLNet_ResolveIP(&ip);
}

void NetworkServer::CheckConnections()
{
	/*int socketRdy;

	socketRdy = SDLNet_CheckSockets(socket_set, 1000);
	
	if (socketRdy > 0)
	{
		client = SDLNet_TCP_Accept(server_socket);
	}*/

	client = SDLNet_TCP_Accept(server_socket);
	if (client == NULL)
	{
		return;
	}

	if (currentCon < maxConnections)
	{
		if (SDLNet_TCP_AddSocket(clientSocketSet, client) == -1)
		{
			fprintf(stderr, "Error SDLNet_TCP_AddSocket: %sn", SDLNet_GetError());
			exit(-1);
		}
	}
	currentCon++;
}

void NetworkServer::SendTest()
{
	/*const char* text = "Hello\n";

	if (client != NULL)
	{
		SDLNet_TCP_Send(client, text, 6);
	}*/
}

void NetworkServer::CloseSocket()
{
	/*if (SDLNet_TCP_DelSocket(socket_set, server_socket) == -1)
	{
		fprintf(stderr, "Error SDLNet_TCP_DelSocket: %sn", SDLNet_GetError());
		exit(-1);
	}*/

	SDLNet_TCP_Close(server_socket);
	//SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
}

void NetworkServer::Encode()
{
}

void NetworkServer::Decode()
{
}
