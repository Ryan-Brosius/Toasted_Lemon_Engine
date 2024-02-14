#include <SDL_net.h>
#include <stdio.h>
#include <iostream>

class NetworkAbstract
{
public:
	virtual void init() = 0;
	virtual void CloseSocket() = 0;
	virtual void Encode() = 0;
	virtual void Decode() = 0;
};

class NetworkServer: public NetworkAbstract
{
public:
	NetworkServer(int maxCon);
	void init();
	void CloseSocket();
	void CheckConnections();
	const char* GetHostName();
	void SendTest();
	void Encode();
	void Decode();

private:
	int next_ind;
	TCPsocket server_socket;
	TCPsocket client;
	IPaddress ip;
	int maxConnections;
	SDLNet_SocketSet clientSocketSet;
	int currentCon;
};

class NetworkClient: public NetworkAbstract
{
public:
	NetworkClient();
	void init();
	void ConnectToHost(const char* pIP, int port);
	void RecvTest();
	void CloseSocket();
	void Encode();
	void Decode();

private:
	TCPsocket socket;
	SDLNet_SocketSet socket_set;
	IPaddress ip;
};