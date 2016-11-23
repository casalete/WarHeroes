#include "Common.h"

#include <cstdlib>
#include <ctime>
#include <vector>

#include "deck.h"

void initRandom()
{
	srand(time(NULL));
	//TODO solve this with reference	
}

std::vector<int>* charDecktoVectorDeck(char* strDeck)
{
	std::vector<int> *vecDeck = new std::vector<int>();
	for (int i = 0; i < NOCARD; ++i)
	{
		while (strDeck[i] > '0')
		{
			vecDeck->push_back(i);
			--strDeck[i];
		}
	}
	return vecDeck;
}


