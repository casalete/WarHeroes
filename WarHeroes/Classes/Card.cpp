#include "Deck.h"
#include "Card.h"
#include <sstream>
USING_NS_CC;

using namespace cocos2d::ui;

Card* Card::create(cardName cardID)
{

	std::stringstream ss;
	ss << "Card" << cardID << ".png";
	std::string str = ss.str();
	
	Card* pSprite = new Card();


	if (pSprite->initWithSpriteFrameName(str))
	{
		pSprite->ID = cardID;
		pSprite->cardInit();
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;

	

}
void Card::cardInit()
{
	// de facut switch cu case pt fiecare carte
	
}
