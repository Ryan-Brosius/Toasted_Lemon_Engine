#include "Networking.h"

NetworkClient::NetworkClient()
{
	/*TCPsocket socket;
	IPaddress ip;*/
}

void NetworkClient::init()
{
	//adding comment
	SDLNet_Init();
	socketSet = SDLNet_AllocSocketSet(1);

	/*socket = SDLNet_TCP_Open(&ip);
	if (socket == NULL)
	{
		fprintf(stderr, "Error SDLNet_TCP_Open: %sn", SDLNet_GetError());
		exit(-1);
	}*/

	/*socket_set = SDLNet_AllocSocketSet(1);
	if (socket_set == NULL)
	{
		fprintf(stderr, "Error SDLNet_AllocSocketSet: %sn", SDLNet_GetError());
		exit(-1);
	}

	if (SDLNet_TCP_AddSocket(socket_set, socket) == -1)
	{
		fprintf(stderr, "Error SDLNet_TCP_AddSocket: %sn", SDLNet_GetError());
		exit(-1);
	}*/
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

void NetworkClient::RecvTest()
{
	/*char text[6];
	
	SDLNet_TCP_Recv(socket, text, 6);
	std::cout << text;*/
}

void NetworkClient::CloseSocket()
{
}

void NetworkClient::Encode()
{
}

void NetworkClient::Decode()
{
}

void NetworkClient::Send(int UID, int x_pos, int y_pos)
{
	sprintf_s(message, "1 %d %d %d", UID, x_pos, y_pos);
	SDLNet_TCP_Send(socket, message, strlen(message) + 1);
}

void NetworkClient::Recieve()
{
	if (SDLNet_CheckSockets(socketSet, 0) && SDLNet_SocketReady(socket))
	{
		int code;
		char UID[20];

		SDLNet_TCP_Recv(socket, incomingMessage, 1024);
		sscanf(incomingMessage, "%d %s", &code, UID);

		std::cout << "Message: " << incomingMessage << "\n";
		switch (code)
		{
		case 0:
			//set UID of player
			break;
		}
	}
}