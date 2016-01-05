#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"

class Player
{
	std::vector<int> shuffledDeck;
	std::vector<int> hand;
	bool turn;
	int gold;
	int mana;
	int heroHP;
	int workers;
	int mine;
	int monastery;
	
	//int gear

	void init();
	void deckShuffler();
	void drawCards(int);
	void placeVillager(int);
	void loseHP(int);
	bool isTurn();
	void endTurn();
	void startTurn();
	std::vector<int> getPlayerDeck();
	

	

};








#endif