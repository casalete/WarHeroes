#ifndef _COMMON__H_
#define _COMMON__H_

#include <cstdlib>
#include <ctime>
#include <vector>

#include "deck.h"

#define SERVER_COMMAND_LENGHT 10

std::vector<int>* charDecktoVectorDeck(char* strDeck);

enum serverCode { SEND_SERVER_INIT, SEND_SERVER_DECK, SEND_SERVER_STARTGAME, SEND_SERVER_DRAWCARD, SEND_SERVER_ENDGAME, SEND_SERVER_FADECARD, SEND_SERVER_PLAYCARD};
enum SoldiersPosition { MY_WAR_1, MY_WAR_2, MY_WAR_3, MY_WAR_4, MY_WAR_5, MY_WAR_6, MY_GUARD_1, MY_GUARD_2, MY_GUARD_GOLD, MY_GUARD_MANA,
	HIS_WAR_1, HIS_WAR_2, HIS_WAR_3, HIS_WAR_4, HIS_WAR_5, HIS_WAR_6, HIS_GUARD_1, HIS_GUARD_2, HIS_GUARD_GOLD, HIS_GUARD_MANA,
	TOTAL_SOLDIERS_BATTLEFIELD
};

void initRandom();

//Should remove this :D 
static const char * securityStringParse = "|thusLMsaid";

#endif // !_COMMON__H_
