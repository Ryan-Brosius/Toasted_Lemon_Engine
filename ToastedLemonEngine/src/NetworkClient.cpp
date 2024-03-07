#include "Networking.h"
#include "Game.h"

NetworkClient::NetworkClient(Game game)
{
	/*TCPsocket socket;
	IPaddress ip;*/
	this->game = game;
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

void NetworkClient::Decode(TCPsocket sender)
{
	int code;
	char content[20];
	int newPlayerUID;
	int myUID;

	sscanf(incomingMessage, "%d", &code);

	std::cout << "Message: " << incomingMessage << "\n";
	switch (code)
	{
	case 0:
		sscanf(incomingMessage, "%d %d", &code, &myUID);
		UID = myUID;
		std::cout << "UID recieved" << "\n";
		break;
	case 1:
		sscanf(incomingMessage, "%d %d", &code, &newPlayerUID);
		game.createNetworkPlayer(newPlayerUID);
		break;
	case 2:
		//parse input info
		break;
	}
}

void NetworkClient::Send(char tempWayOfSendingInput)
{
	sprintf_s(message, "2 %d %d", UID, tempWayOfSendingInput);
	SDLNet_TCP_Send(socket, message, strlen(message) + 1);
}

void NetworkClient::Recieve()
{
	if (SDLNet_CheckSockets(socketSet, 0) && SDLNet_SocketReady(socket))
	{
		SDLNet_TCP_Recv(socket, incomingMessage, 1024);
		Decode(socket);
	}
}
