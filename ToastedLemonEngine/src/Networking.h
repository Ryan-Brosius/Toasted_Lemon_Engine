#define _CRT_SECURE_NO_WARNINGS //just so the compiler wont be a pain in the ass and raise an error just for using sscanf

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
protected:
	char message[1024];
	char incomingMessage[1024];
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
	void Update();

private:
	//int next_ind;
	TCPsocket server_socket;
	TCPsocket client;
	IPaddress ip;
	int maxConnections;
	SDLNet_SocketSet clientSocketSet;
	int currentCon;
	int curUID;
	TCPsocket* clients;
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
	void Send(int UID, int x_pos, int y_pos);
	void Recieve();

private:
	TCPsocket socket;
	//SDLNet_SocketSet socket_set;
	IPaddress ip;
	SDLNet_SocketSet socketSet;
};