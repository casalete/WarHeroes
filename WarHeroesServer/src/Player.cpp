#include "Player.h"

#include <cstdlib>

#include "Deck.h"
#include "Connection.h"

void readThreadLoop(Player* player)
{
	player->readData();
}

Player::Player(std::vector<int> * customDeck, SOCKET fd)
{
	_connection = new Connection(fd);
	while (customDeck->size())
	{
		int	x = rand() % customDeck->size();
		shuffledDeck.push_back((cardName)(*customDeck)[x]);
		customDeck->erase(customDeck->begin() + x);
	}
	delete customDeck;
	Initialize();
}

Player::~Player()
{
	_connection->closeConnection();
	readClientThread->join();
	delete readClientThread;
	delete _connection;
}

Player * Player::create(std::vector<int> * customDeck, SOCKET fd)
{
	Player *pRet = new Player(customDeck, fd);
	if (pRet)
	{
		pRet->readClientThread = new std::thread(readThreadLoop, pRet);
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
	return NULL;
}


void Player::Initialize()
{
	mana = 0;
	gold = 0;
	heroHP = 30;
	workers = 1;
	drawCards(5);
}

int Player::sendData(std::string &data)
{
	return _connection->sendData(data);
}
void Player::readData()
{
	while (_connection && _connection->isConnected())// todo make it stop from a toggle.
	{
		_connection->readData(clientBuffer);
	}
}

std::string Player::readCommand()
{
	std::string::iterator i;
	std::string serverCommand = "";

	std::lock_guard<std::mutex> lock_buffer(_connection->mutexLockString);
	for (i = clientBuffer.begin(); i != clientBuffer.end(); ++i)
	{
		if (*i == ';')
			break;
	}
	if (i != clientBuffer.end())
	{
		serverCommand = clientBuffer.substr(0, ++i - clientBuffer.begin());
		clientBuffer.erase(clientBuffer.begin(), i);
	}
	return serverCommand;
}

cardName Player::drawCard()
{
	if (!shuffledDeck.empty())
	{
		cardName card = shuffledDeck.back();
		shuffledDeck.pop_back();
		hand.push_back(card);
		return card;
	}
	return NOCARD;
}

void Player::drawCards(int nrCards)
{
	for (int i = 1; i <= nrCards; i++)
	{
		cardName cardID = shuffledDeck.back();
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
std::vector<cardName> Player::getPlayerDeck()
{
	std::vector<cardName> deck;

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
				deck.push_back((cardName)i);
				--inputChar;
			}
		}
	fclose(fin);
	return deck;
}
