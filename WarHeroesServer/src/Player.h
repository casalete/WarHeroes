#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <vector>
#include <thread>

#include "Connection.h"
#include "Common.h"

class Player
{
	std::thread * readClientThread;
	std::string clientBuffer;

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
	void readData();
	std::string readCommand();
	cardName drawCard();
	static Player * create(std::vector<int> * customDeck, SOCKET fd);
};

#endif // !_PLAYER__H_
