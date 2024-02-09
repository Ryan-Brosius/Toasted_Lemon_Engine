#include "Networking.h"

#define MAX_SOCKETS 4

NetworkServer::NetworkServer()
{
	int next_ind = 0;
	TCPsocket server_socket;
	TCPsocket client;
	SDLNet_SocketSet socket_set;
	TCPsocket sockets[MAX_SOCKETS];
	IPaddress ip;
}

void NetworkServer::init()
{
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

	socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS + 1);
	if (socket_set == NULL)
	{
		fprintf(stderr, "Error SDLNet_AllocSocketSet: %sn", SDLNet_GetError());
		exit(-1);
	}

	if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1)
	{
		fprintf(stderr, "Error SDLNet_TCP-AddSocket: %sn", SDLNet_GetError());
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
}

void NetworkServer::SendTest()
{
	const char* text = "Hello\n";

	if (client != NULL)
	{
		SDLNet_TCP_Send(client, text, 6);
	}
}
void NetworkServer::CloseServer()
{
	if (SDLNet_TCP_DelSocket(socket_set, server_socket) == -1)
	{
		fprintf(stderr, "Error SDLNet_TCP_DelSocket: %sn", SDLNet_GetError());
		exit(-1);
	}

	SDLNet_TCP_Close(server_socket);
	SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
}
