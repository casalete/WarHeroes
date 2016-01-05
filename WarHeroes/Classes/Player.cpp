#include "Player.h"
#include "Deck.h"
USING_NS_CC;

using namespace cocos2d::ui;


void Player::init()
{
	mana = 0;
	gold = 0;
	heroHP = 30;
	workers = 1;
	deckShuffler();
	drawCards(5);
}
void Player::deckShuffler()
{
	
	
	std::vector<int> CustomDeck = getPlayerDeck();
	while (CustomDeck.size())
	{
		int	x = random() % CustomDeck.size();
		shuffledDeck.push_back(CustomDeck[x]);
		CustomDeck.erase(CustomDeck.begin() + x);
		
	}
	
}
void Player::drawCards(int nrCards)
{
	for (int i = 1; i <= nrCards; i++)
	{
		int cardID = shuffledDeck.back();
		hand.push_back(cardID);
			shuffledDeck.pop_back();
	}
}
void Player::placeVillager(int job)
{
	// 1 = mine ; 2 = monastery
	if (job == 1)
	{
		mine++;
	}
	if (job == 2)
	{

		monastery++;
	}
	workers--;
	
}
void Player::loseHP(int dHP)
{
	heroHP = heroHP - dHP;
}
bool Player::isTurn()
{
	return turn;
}
void Player::endTurn()
{
	turn = false;

}
void Player::startTurn()
{
	turn = true;
	gold = gold + mine;
	mana = mana + monastery;
	drawCards(1);
}
std::vector<int> Player::getPlayerDeck()
{
	return{ };
}  