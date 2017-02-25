#include "Game.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#include "deck.h"
#include "Common.h"

#define BUFFER_SIZE 2000
#define NUMBER_PLAYERS 1

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
	serverCode command;
	int keepGoing = 1, input;
	std::string data(SERVER_COMMAND_LENGHT, 0);
	data[0] = '$';
	data[SERVER_COMMAND_LENGHT - 1] = ';';
	while (keepGoing)
	{
		fprintf(stdout, "\n$");
		fscanf_s(stdin, "%d", &command);
		data[1] = command;
		switch (command)
		{
		case SEND_SERVER_INIT:
			break;
		case SEND_SERVER_DECK:
			break;
		case SEND_SERVER_STARTGAME:
			player[0]->sendData(data);
			break;
		case SEND_SERVER_DRAWCARD:
			fprintf(stdout, "Who (0 you, 1 him) :");
			fscanf_s(stdin, "%d", &input);
			data[2] = input;
			//fprintf(stdout, "What Card:");
			//fscanf_s(stdin, "%d", &input);
			input = (int)player[0]->drawCard();
			data[3] = input >> 8;
			data[4] = input % (1 << 8);
			player[0]->sendData(data);
			break;
		case SEND_SERVER_ENDGAME:
			player[0]->sendData(data);
			keepGoing = 0;
			break;
		case SEND_SERVER_FADECARD:
			fprintf(stdout, "What Card:");
			fscanf_s(stdin, "%d", &input);
			data[2] = input;
			fprintf(stdout, "Opacity:");
			fscanf_s(stdin, "%d", &input);
			data[3] = input;
			player[0]->sendData(data);
			break;
		case SEND_SERVER_PLAYCARD:
			fprintf(stdout, "What Card:");
			fscanf_s(stdin, "%d", &input);
			data[2] = input;
			fprintf(stdout, "Where:");
			fscanf_s(stdin, "%d", &input);
			data[3] = input;
			player[0]->sendData(data);
			break;
		case SEND_SERVER_READINFO:
			processCommands(0);
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
	for (int j = 0; j < NUMBER_PLAYERS; ++j)
	{
		if ((errCode = _server->acceptPlayer(j)))
		{
			fprintf_s(stderr, "acceptPlayers(%d) returned %d\n", j, errCode);
		}
	}
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

void Game::processCommands(float dt)
{
	for (int j = 0; j < NUMBER_PLAYERS; ++j)
	{
		std::string clientCommand = player[j]->readCommand();
		player[j]->sendData(clientCommand);// this is only for testing
	}
}
