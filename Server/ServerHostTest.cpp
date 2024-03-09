#define _CRT_SECURE_NO_WARNINGS //just so the compiler wont be a pain in the ass and raise an error just for using sscanf
#include "Networking.h"

int main(int argc, char* argv[]) {


	NetworkServer server = NetworkServer(4);
	server.init();
	std::cout << server.GetHostName();

	while (true)
	{
		server.CheckConnections();
	}

	return 0;
}