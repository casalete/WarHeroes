#ifndef _COMMON__H_
#define _COMMON__H_

#include <cstdlib>
#include <ctime>
#include <vector>

#include "deck.h"

std::vector<int>* charDecktoVectorDeck(char* strDeck);

void initRandom();

static const char * securityStringParse = "|thusLMsaid";

#endif // !_COMMON__H_

