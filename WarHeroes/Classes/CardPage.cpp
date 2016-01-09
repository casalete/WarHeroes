#include "CardPage.h"
#include "cocos2d.h"
#include "Deck.h"
#include "DeckBuilder.h"

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
		//creating the card
		char str[15];
		sprintf(str, "card%d.png", (pageNumber * 8 + i) % 24);
		//sprintf(str, "card%d.png", /*pageNumber * 8 +*/ i); // the line above is for debug
		Sprite *card = Sprite::create(str);
		card->setPosition(Vec2(winsize.width / 2 + ((i%4) - 1.5) * card->getContentSize().width * 1.5, winsize.height / 2 + (0.6 - (i/4)) * card->getContentSize().height * 1.1));
		card->setTag(i);
		addChild(card);

		//adding the buttons
		MenuItemImage *btnPlus = MenuItemImage::create("btnPlus.png", "btnPlus.png", "btnPlus.png", CC_CALLBACK_1(CardPage::addCardToDeck, this, pageNumber * 8 + i));
		btnPlus->setPositionY(btnPlus->getContentSize().height);
		MenuItemImage *btnMinus = MenuItemImage::create("btnMinus.png", "btnMinus.png", "btnPlus.png", CC_CALLBACK_1(CardPage::removeCardFromDeck, this, pageNumber * 8 + i));
		btnMinus->setPositionY(-btnPlus->getContentSize().height);
		Menu* menu = Menu::create(btnPlus, btnMinus, NULL);
		menu->setPosition(Vec2(-btnPlus->getContentSize().width / 2, card->getContentSize().height / 2));
		card->addChild(menu, 1);

		Label* nrDuplicate = Label::createWithTTF("0", "ITCKRIST.TTF", 30);
		nrDuplicate->setPosition(Vec2(-btnPlus->getContentSize().width / 2, card->getContentSize().height / 2));
		nrDuplicate->setTag(7);
		card->addChild(nrDuplicate);
		
	}
	
	return true;
}
void CardPage::initTextLabels()
{
	short maxi;
	if (pageNumber * 8 + 8 > (int)NOCARD)
		maxi = (int)NOCARD % 8;
	else
		maxi = 8;

	for (short i = 0; i < maxi; ++i)
	{
		char str[5];
		sprintf(str, "%d", ((DeckBuilder*)(getParent()))->getCardOccurrence(pageNumber * 8 + i));;
		((Label*)(getChildByTag(i)->getChildByTag(7)))->setString(str);
	}
}
void CardPage::addCardToDeck(Ref*ref, int ID)
{
	int noDuplicate = ((DeckBuilder*)(getParent()))->modifyCardOccurrence(ID, 1);
	char str[5];
	sprintf(str, "%d", noDuplicate);
	((Label*)(getChildByTag(ID % 8)->getChildByTag(7)))->setString(str);
}
void CardPage::removeCardFromDeck(Ref*ref, int ID)
{
	int noDuplicate = ((DeckBuilder*)(getParent()))->modifyCardOccurrence(ID, -1);
	char str[5];
	sprintf(str, "%d", noDuplicate);
	((Label*)(getChildByTag(ID % 8)->getChildByTag(7)))->setString(str);
}