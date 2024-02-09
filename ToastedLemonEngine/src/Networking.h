#include <SDL_net.h>
#include <stdio.h>
#include <iostream>

class NetworkServer
{
public:
	NetworkServer();
	void init();
	void CloseServer();
	void CheckConnections();
	const char* GetHostName();
	void SendTest();

private:
	int next_ind;
	TCPsocket server_socket;
	TCPsocket client;
	SDLNet_SocketSet socket_set;
	TCPsocket sockets;
	IPaddress ip;
};

class NetworkClient
{
public:
	NetworkClient();
	void init(const char* pIP, int port);
	void RecvTest();

private:
	TCPsocket socket;
	SDLNet_SocketSet socket_set;
	IPaddress ip;
};