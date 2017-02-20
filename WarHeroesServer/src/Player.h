#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <vector>

#include "Connection.h"
#include "Common.h"

class Player
{
	std::vector<cardName> shuffledDeck;
	std::vector<cardName> hand;
	bool turn;
	int gold;
	int mana;
	int heroHP;
	int workers;
	int mine;
	int monastery;
	int playerID;

	Connection *_connection;

	//int gear

	void Initialize();
	void drawCards(int);
	void placeVillager(int);
	void loseHP(int);
	bool isTurn();
	void endTurn();
	void startTurn();
	std::vector<cardName> getPlayerDeck();
public:
	Player(std::vector<int>*, SOCKET);
	~Player();
	int sendData(std::string&);
	cardName drawCard();
	static Player * create(std::vector<int> * customDeck, SOCKET fd);
};

#endif // !_PLAYER__H_
