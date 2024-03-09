#include "Networking.h"
#include "Game.h"

NetworkClient::NetworkClient(Game game)
{
	/*TCPsocket socket;
	IPaddress ip;*/
	//this->game = game;
	return;
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
	int UIDbuffer;
	int incomingUID;
	double xpos;
	double ypos;
	int anim;

	sscanf(incomingMessage, "%d", &code);

	std::cout << "Message: " << incomingMessage << "\n";
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
		sscanf(incomingMessage, "%d %d %lf %lf", &code, &UIDbuffer, &xpos, &ypos);
		if (xpos != NULL && ypos != NULL)
		{
			game->moveNetPlayer(UIDbuffer, xpos, ypos);
		}
		break;
	case 3:
		sscanf(incomingMessage, "%d %d", &code, &UIDbuffer, &anim);
		game->setAnimNetPlayer(UIDbuffer, anim);
		break;
	}
}

void NetworkClient::Send()
{
	double* position = (double*) malloc(sizeof(double) * 2);
	int* anim = (int*) malloc(sizeof(int));

	game->GetPlayerPosition(position);
	game->GetPlayerAnim(anim);

	if (*position != NULL && *(position + 1) != NULL)
	{
		sprintf(message, "2 %d %f %f\n", UID, *position, *(position + 1));
		SDLNet_TCP_Send(socket, message, strlen(message) + 1);
	}

	if (*anim != NULL)
	{
		std::cout << *anim << std::endl;
		sprintf(message, "3 %d %d\n", UID, *anim);
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
