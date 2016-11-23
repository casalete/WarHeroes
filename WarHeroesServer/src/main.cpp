#include <fstream>

#include <cstdio>

#include "Common.h"
#include "Game.h"

void startTUI()
{
	fprintf(stdout, "Do you want to host a game?(y/n)\n");
	char s;
	int keepGoing = 1;
	Game * _game;
	while (keepGoing)
	{
		fscanf_s(stdin, "%c", &s);
		if (s == 'y' || s == 'Y')
		{ 
			_game = new Game();
			fprintf(stdout, "Game now starting!\n");
			_game->RunGame();
			delete _game;
			fprintf(stdout, "Do you want to host another game?(y/n)\n");
		}
		else if (s == 'n' || s == 'N')
		{
			keepGoing = 0;
		}
	}
}

int main()
{
	initRandom();
	startTUI();

}