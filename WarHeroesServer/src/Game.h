#ifndef _GAME__H_
#define _GAME__H_

#include <vector>
#include <WinSock2.h>
#include <WS2TCPIP.H>

#include "Player.h"

#define PORT "27015"

class Game
{
	SOCKET serverDescriptor;
	Player * player[2];
	int setupSockets();
	int acceptPlayers();
	std::vector<int> parseDeck(const char*);
public:
	void RunGame();
	Game();
	~Game();
};

#endif // !_GAME__H_
