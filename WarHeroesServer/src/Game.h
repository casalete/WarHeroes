#ifndef _GAME__H_
#define _GAME__H_

#include <vector>
#include <WinSock2.h>
#include <WS2TCPIP.H>

#include "Player.h"
#include "Server.h"

#define PORT "27015"

class Game
{
	Player * player[2];
	Server * _server;
	//SOCKET serverDescriptor;
	//int setupSockets();
	//int acceptPlayers();
	//std::vector<int> parseDeck(const char*);

	int CLItesting();
public:
	void RunGame();
	Game();
	~Game();
};

#endif // !_GAME__H_
