#include "CardPage.h"
#include "cocos2d.h"
#include "Deck.h"

using namespace cocos2d::ui;
using namespace cocos2d;


CardPage* CardPage::create(int i)
{
	if ((i < 0) || (i > ((int)NOCARD) / 8))
		return NULL;

	CardPage *pRet = new(std::nothrow) CardPage(i);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool CardPage::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::Size winsize = Director::getInstance()->getWinSize();

	short maxi;
	if (pageNumber * 8 + 8 > (int)NOCARD)
		maxi = (int)NOCARD % 8;
	else
		maxi = 8;

	for (short i = 0; i < maxi; ++i)
	{
		char str[15];
		sprintf(str, "card%d.png", /*pageNumber * 8 + */i);
		Sprite *card = Sprite::create(str);
		card->setPosition(Vec2(winsize.width / 2 + ((i%4) - 1.5) * card->getContentSize().width * 1.5, winsize.height / 2 + (0.5 - (i/4)) * card->getContentSize().height * 1.1));
		addChild(card);
	}
	
	return true;
}