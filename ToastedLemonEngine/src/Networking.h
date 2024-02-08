#include <SDL_net.h>
#include <stdio.h>
#include <iostream>

class NetworkServer
{
public:
	NetworkServer();
	void init();

private:
	int next_ind;
	TCPsocket server_socket;
	//Client clients[MAX_SOCKETS];
	SDLNet_SocketSet socket_set;
	TCPsocket sockets;
	IPaddress ip;
};

class NetworkClient
{
public:
	NetworkClient();
	void init(char* pIP, int port);

private:
	TCPsocket socket;
	SDLNet_SocketSet socket_set;
	IPaddress ip;
};