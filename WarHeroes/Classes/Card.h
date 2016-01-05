#ifndef __CARD_H__
#define __CARD_H__
#include "cocos2d.h"
#include "deck.h"

class Card : public cocos2d::Sprite
{
	cardName ID;
	int manaCost;
	int goldCost;
	int attack;
	int health;
	std::string ability;

	static Card *create(cardName);
	void cardInit();

};

#endif