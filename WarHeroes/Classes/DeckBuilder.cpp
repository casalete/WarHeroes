#include "Deck.h"
#include "DeckBuilder.h"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace cocos2d;

const int maxDuplicateCards = 4;
const int maxCards = 40;

Scene* DeckBuilder::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DeckBuilder::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool DeckBuilder::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Sprite *backgroundSprite = Sprite::create("paperWallpaper.jpg");
	addChild(backgroundSprite);

	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	backgroundSprite->setScaleX(winsize.width / backgroundSprite->getContentSize().width);
	backgroundSprite->setScaleY(winsize.height / backgroundSprite->getContentSize().height);
	backgroundSprite->setPosition(winsize.width / 2.0, winsize.height / 2.0);

	//init cardsInDeck
	for (int i = 0; i < NOCARD; ++i)
	{
		cardsInDeck[i] = 0;
	}
	

	//Buttons (next & previous)

	Menu *menu = Menu::create();
	addChild(menu);

	Sprite *nextSprite = Sprite::create("nextBtn.png");
	MenuItemSprite* btnNext = MenuItemSprite::create(nextSprite, nextSprite, nextSprite, this, menu_selector(DeckBuilder::NextPage));
	btnNext->setVisible(true);
	btnNext->setPositionX((winsize.width / 2) - (nextSprite->getContentSize().width)/3);
	menu->addChild(btnNext);
	
	Sprite *prevSprite = Sprite::create("prevBtn.png");
	MenuItemSprite* btnPrev = MenuItemSprite::create(prevSprite, prevSprite, prevSprite, this, menu_selector(DeckBuilder::PreviousPage));
	btnPrev->setVisible(true);
	btnPrev->setPositionX(-(winsize.width / 2) + (prevSprite->getContentSize().width)/3);
	menu->addChild(btnPrev);

	char str[8];
	sprintf(str, "%d/%d", cardsSelected = 0, maxCards);
	Label* deckNr = Label::createWithTTF(str, "ITCKRIST.TTF", 40);
	deckNr->setPosition(Vec2(winsize.width / 2, winsize.height - prevSprite->getContentSize().height / 3));
	deckNr->setTag(7);
	addChild(deckNr);

	pageNumber = 0;
	previousPage = CardPage::create(-1);
	curentPage = CardPage::create(0);
	nextPage = CardPage::create(1);
	addChild(curentPage);
	curentPage->initTextLabels();
	if (nextPage)
	{
		nextPage->setPositionX(winsize.width);
		addChild(nextPage);
		nextPage->initTextLabels();
	}

	return true;
}
void DeckBuilder::NextPage(Ref *ref)
{
	if (!nextPage)
		return;
	cocos2d::Size winsize = Director::getInstance()->getWinSize();

	if (previousPage)
	{
		previousPage->removeFromParent();
	}
	previousPage = curentPage;
	curentPage = nextPage;
	nextPage = CardPage::create(++pageNumber + 1);
	if (nextPage)
	{
		nextPage->setPosition(Vec2(winsize.width, 0));
		curentPage->getParent()->addChild(nextPage);
		nextPage->initTextLabels();
	}

	previousPage->runAction(MoveTo::create(0.5, Vec2(-winsize.width, 0)));
	curentPage->runAction(MoveTo::create(0.5, Vec2(0, 0)));
}
void DeckBuilder::PreviousPage(Ref *ref)
{
	if (!previousPage)
		return;
	cocos2d::Size winsize = Director::getInstance()->getWinSize();

	if (nextPage)
	{
		nextPage->removeFromParent();
	}
	nextPage = curentPage;
	curentPage = previousPage;
	previousPage = CardPage::create(--pageNumber - 1);
	if (previousPage)
	{
		previousPage->setPosition(Vec2(-winsize.width, 0));
		curentPage->getParent()->addChild(previousPage);
		previousPage->initTextLabels();
	}

	nextPage->runAction(MoveTo::create(0.5, Vec2(winsize.width, 0)));
	curentPage->runAction(MoveTo::create(0.5, Vec2(0, 0)));

}

int DeckBuilder::modifyCardOccurrence(int ID, int di)
{
	int newCardNo = cardsInDeck[ID] + di;
	
	if ((cardsSelected + di > maxCards) || (newCardNo > maxDuplicateCards) || (newCardNo < 0))
	{
		return cardsInDeck[ID];
	}

	char str[8];
	cardsSelected += di;
	sprintf(str, "%d/%d", cardsSelected, maxCards);
	((Label*)(getChildByTag(7)))->setString(str);

	return (cardsInDeck[ID] = newCardNo);
}

int DeckBuilder::getCardOccurrence(int ID)
{
	return cardsInDeck[ID];
}