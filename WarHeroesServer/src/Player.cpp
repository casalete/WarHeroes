#include "Player.h"

#include <cstdlib>

#include "Deck.h"


Player::Player(std::vector<int> * customDeck, SOCKET fd)
{
	_connection = new Connection(fd);
	while (customDeck->size())
	{
		int	x = rand() % customDeck->size();
		shuffledDeck.push_back((*customDeck)[x]);
		customDeck->erase(customDeck->begin() + x);
	}
	delete customDeck;
	Initialize();
}

Player::~Player()
{
	delete _connection;
}

void Player::Initialize()
{
	mana = 0;
	gold = 0;
	heroHP = 30;
	workers = 1;
	drawCards(5);
}
void Player::drawCards(int nrCards)
{
	for (int i = 1; i <= nrCards; i++)
	{
		int cardID = shuffledDeck.back();
		hand.push_back(cardID);
		shuffledDeck.pop_back();
		//TODO: Tell client what he had drawn
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
	std::vector<int> deck;

	char str[15];
	sprintf_s(str, "Player%d.data", playerID);

	char inputChar;

	FILE * fin /*= fopen(str, "r")*/;
	fopen_s(&fin, str, "r");
	if (fin)
		for (int i = 0; i < NOCARD; ++i)
		{
			fscanf_s(fin, "%c", &inputChar);
			while (inputChar > '0')
			{
				deck.push_back(i);
				--inputChar;
			}
		}
	fclose(fin);
	return deck;
}