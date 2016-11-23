#ifndef _SERVER__H_
#define _SERVER__H_

#include <WinSock2.h>
#include <WS2TCPIP.H>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#include "Player.h"

class Server
{
private:
	SOCKET serverDescriptor;
	int setupSockets();
	Player** _players;
public:
	int sendData(int, std::string&);
	int acceptPlayer(int);
	Server(Player**);
	~Server();
};

#endif // !_SERVER__H_
