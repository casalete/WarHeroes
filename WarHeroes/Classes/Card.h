#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
#include "deck.h"

enum cardRole { ROLE_INHAND, ROLE_WARRIOR, ROLE_GUARDIAN };
enum classType { CLASS_CAVALERY, CLASS_INFANTRY, CLASS_ARCHER, CLASS_SIEGE, CLASS_SPELL };

class Card : public cocos2d::Sprite
{
private:
	cardName ID;
	int manaCost;
	int goldCost;
	int attack;
	int health;
	std::string ability;

	cardRole role;
	int slot;
	classType type;

	void cardInit();
public:
	bool isMouseOver(cocos2d::Vec2);
	void enterScroll();
	void exitScroll();
	void moveScroll(cocos2d::Vec2);
	cardName getCardID();

	int getSlot();
	void setSlot(int);
	cardRole getRole();
	void setRole(cardRole);
	classType getType();

	static Card *create(cardName);
};

#endif