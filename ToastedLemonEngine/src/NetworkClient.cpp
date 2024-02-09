#include "Networking.h"

NetworkClient::NetworkClient()
{
	TCPsocket socket;
	SDLNet_SocketSet socket_set;
	IPaddress ip;
}

void NetworkClient::init(const char* pIP, int port)
{
	if (SDLNet_ResolveHost(&ip, pIP, port) == -1)
	{
		fprintf(stderr, "Error SDLNet_ResolveHose: %sn", SDLNet_GetError());
		exit(-1);
	}

	socket = SDLNet_TCP_Open(&ip);
	if (socket == NULL)
	{
		fprintf(stderr, "Error SDLNet_TCP_Open: %sn", SDLNet_GetError());
		exit(-1);
	}

	socket_set = SDLNet_AllocSocketSet(1);
	if (socket_set == NULL)
	{
		fprintf(stderr, "Error SDLNet_AllocSocketSet: %sn", SDLNet_GetError());
		exit(-1);
	}

	if (SDLNet_TCP_AddSocket(socket_set, socket) == -1)
	{
		fprintf(stderr, "Error SDLNet_TCP_AddSocket: %sn", SDLNet_GetError());
		exit(-1);
	}
}

void NetworkClient::RecvTest()
{
	char text[100];
	
	SDLNet_TCP_Recv(socket, text, 6);
	std::cout << text;
}