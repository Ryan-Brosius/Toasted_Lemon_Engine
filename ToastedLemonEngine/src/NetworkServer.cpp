#include "Networking.h"

/*TODO: setup some way for server to map UIDs to sockets
* clean up code
* remove comments
* */

NetworkServer::NetworkServer(int maxCon)
{
	//next_ind = 0;
	/*TCPsocket server_socket;
	TCPsocket client;
	IPaddress ip;
	int maxConnections;
	SDLNet_SocketSet clientSocketSet;
	int currentCon;*/

	maxConnections = maxCon;
	curUID = 0;
	clients = (TCPsocket*) malloc(sizeof(TCPsocket) * maxCon);
}

void NetworkServer::init()
{
	currentCon = 0;

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "Error SDL_Init: %s\n", SDL_GetError());
		exit(-1);
	}

	if (SDLNet_Init() == -1)
	{
		fprintf(stderr, "Error SDLNet_Init: %s\n", SDLNet_GetError());
	}

	if (SDLNet_ResolveHost(&ip, NULL, 8099) == -1)
	{
		fprintf(stderr, "Error SDLnet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-1);
	}

	server_socket = SDLNet_TCP_Open(&ip);

	if (server_socket == NULL)
	{
		fprintf(stderr, "Error SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(-1);
	}

	clientSocketSet = SDLNet_AllocSocketSet(maxConnections);
	if (clientSocketSet == NULL)
	{
		fprintf(stderr, "Error SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(-1);
	}
}

const char* NetworkServer::GetHostName()
{
	std::cout << SDLNet_ResolveIP(&ip) << "\n";
	return SDLNet_ResolveIP(&ip);
}

void NetworkServer::CheckConnections()
{
	/*if (socketRdy == 0)
	{
		std::cout << "none accepted\n";
		return;
		//client = SDLNet_TCP_Accept(server_socket);
	}*/

	client = SDLNet_TCP_Accept(server_socket);

	if (client == NULL)
	{
		return;
	}

	if (client != NULL)
	{
		std::cout << "CLIENT CONNECTED!!" << std::endl;
	}

	if (currentCon < maxConnections)
	{
		if (SDLNet_TCP_AddSocket(clientSocketSet, client) == -1)
		{
			fprintf(stderr, "Error SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
			exit(-1);
		}

		sprintf(message, "1 %d \n", curUID);
		for (int i = 0; i < currentCon; i++)
		{
			SDLNet_TCP_Send(*(clients + i), message, strlen(message) + 1);
		}

		for (int i = 0; i < currentCon; i++)
		{
			//TODO: actually make this send UID of players instead
			sprintf(message, "1 %d \n", i);
			SDLNet_TCP_Send(client, message, strlen(message) + 1);
		}

		*(clients + currentCon) = client;
		currentCon++;
		sprintf(message, "0 %d \n", curUID);
		SDLNet_TCP_Send(client, message, strlen(message) + 1);
		curUID++;
	}
	
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
	free(clients);
	//SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
}

void NetworkServer::Encode()
{
}

void NetworkServer::Decode(TCPsocket sender)
{
	int code;
	char senderID[20];
	char input[20];

	sscanf(incomingMessage, "%d", &code);

	switch (code)
	{
	case 2:
		sscanf(incomingMessage, "%d %s %s", &code, senderID, input);

		for (int i = 0; i < currentCon; i++)
		{
			if (*(clients + i) == sender)
			{
				continue;
			}

			SDLNet_TCP_Send(*(clients + i), incomingMessage, 1024);
		}
		break;
	}
}

void NetworkServer::Send()
{}

void NetworkServer::Recieve()
{
	if (SDLNet_CheckSockets(clientSocketSet, 0))
	{
		for (int i = 0; i < currentCon; i++)
		{
			if (SDLNet_SocketReady(*(clients + i)))
			{
				SDLNet_TCP_Recv(*(clients + i), incomingMessage, 1024);
				Decode(*(clients + i));
			}
		}
	}
}




void NetworkServer::Update()
{
	if (SDLNet_CheckSockets(clientSocketSet, 0) > 0)
	{
		for (int i = 0; i < currentCon; i++)
		{
			if (SDLNet_SocketReady(clients[i]))
			{
				SDLNet_TCP_Recv(clients[i], incomingMessage, 1024);

				for (int k = 0; k < currentCon; k++)
				{
					if (k != i)
					{
						SDLNet_TCP_Send(clients[k], incomingMessage, strlen(incomingMessage) + 1);
					}
				}
			}
		}
	}
}

