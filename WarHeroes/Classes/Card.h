#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
#include "deck.h"

enum cardRole { ROLE_INHAND, ROLE_WARRIOR, ROLE_GUARDIAN };
enum classType { CLASS_CAVALERY, CLASS_INFANTRY, CLASS_ARCHER, CLASS_SIEGE, CLASS_SPELL, CLASS_CASTER, CLASS_SUPPORT};

class Card : public cocos2d::Sprite
{
private:
	cardName ID;
	int manaCost; //can remove
	int goldCost; //can remove
	int attack;
	int health;
	int active;
	std::string ability;// Do not need - abilities and game-mech happen on Server ONLY
	// Therefore we can stick to just Graphics

	cocos2d::Label * hpLabel;
	cocos2d::Label * atkLabel;
	cocos2d::Layer * cardLayout;

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