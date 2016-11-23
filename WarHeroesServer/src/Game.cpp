#include "Game.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#include "deck.h"
#include "Common.h"

#define BUFFER_SIZE 2000


//std::vector<int> Game::parseDeck(const char * buffer)
//{
//	std::vector<int> v;
//	for (int i = 0; i < NOCARD; ++i)
//	{
//		v.push_back(buffer[i]);
//	}
//	return v;
//}

int Game::CLItesting()
{
	fprintf(stdout, "You may start sending commands");
	serverCode input;
	int keepGoing = 1;
	std::string data(SERVER_COMMAND_LENGHT, 0);
	data[0] = '$';
	data[SERVER_COMMAND_LENGHT - 1] = ';';
	while (keepGoing)
	{
		fprintf(stdout, "\n$");
		fscanf_s(stdin, "%d", &input);
		switch (input)
		{
		case SEND_SERVER_INIT:
			break;
		case SEND_SERVER_DECK:
			break;
		case SEND_SERVER_STARTGAME:
			data[1] = SEND_SERVER_STARTGAME;
			player[0]->sendData(data);
			break;
		case SEND_SERVER_DRAWCARD:
			data[1] = SEND_SERVER_DRAWCARD;
			fprintf(stdout, "Who (0 you, 1 him) :");
			fscanf_s(stdin, "%d", &input);
			data[2] = input;
			fprintf(stdout, "What Card:");
			fscanf_s(stdin, "%d", &input);
			data[3] = input >> 8;
			data[4] = input % (1 << 8);
			player[0]->sendData(data);
			break;
		case SEND_SERVER_ENDGAME:
			data[1] = SEND_SERVER_ENDGAME;
			player[0]->sendData(data);
			keepGoing = 0;
			break;
		default:
			keepGoing = 0;
			break;
		}
	}
	return 0;
}

void Game::RunGame() {
	int errCode;
	if ((errCode = _server->acceptPlayer(0)))
	{
		fprintf_s(stderr, "acceptPlayers(0) returned %d\n", errCode);
	}
	// uncomment the lower part to connect 2nd player
	/*if ((errCode = _server->acceptPlayer(1)))
	{
		fprintf_s(stderr, "acceptPlayers(1) returned %d\n", errCode);
	}*/
	fprintf_s(stderr, "we are done connecting!\n");
	CLItesting();
}

Game::Game()
{
	_server = new Server(player);
}


Game::~Game()
{
	delete _server;
}

