#ifndef _COMMON__H_
#define _COMMON__H_

#include <cstdlib>
#include <ctime>
#include <vector>

#include "deck.h"

#define SERVER_COMMAND_LENGHT 10

std::vector<int>* charDecktoVectorDeck(char* strDeck);

enum serverCode { SEND_SERVER_INIT, SEND_SERVER_DECK, SEND_SERVER_STARTGAME, SEND_SERVER_DRAWCARD, SEND_SERVER_ENDGAME};

void initRandom();

static const char * securityStringParse = "|thusLMsaid";

#endif // !_COMMON__H_
