#include "Deck.h"
#include "DeckBuilder.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d::ui;
using namespace cocos2d;

const int maxDuplicateCards = 4;
const int maxCards = 40;

Scene* DeckBuilder::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DeckBuilder::create(1);

	// add layer as a child to scene
	scene->addChild(layer);

	layer->createTwin();
	// return the scene
	return scene;
}


DeckBuilder* DeckBuilder::create(int i)
{
	if ((i < 0) || (i >((int)NOCARD) / 8))
		return NULL;

	DeckBuilder *pRet = new(std::nothrow) DeckBuilder(i);
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

void DeckBuilder::createTwin()
{
	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	twinLayer = DeckBuilder::create(2);
	twinLayer->setTwin(this);
	getParent()->addChild(twinLayer);
	twinLayer->setPosition(Vec2(0, -winsize.height));
}

void DeckBuilder::setTwin(DeckBuilder* twin)
{
	twinLayer = twin;
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

	Sprite *backSprite = Sprite::create("btnBack.png");
	MenuItemSprite* btnBack = MenuItemSprite::create(backSprite, backSprite, backSprite, this, menu_selector(DeckBuilder::HomeScene));
	btnBack->setVisible(true);
	btnBack->setPositionX((-winsize.width/2)+(backSprite->getContentSize().width));
	btnBack->setPositionY((-winsize.height/2)+(backSprite->getContentSize().height/2));
	menu->addChild(btnBack);
	
	Sprite *prevSprite = Sprite::create("prevBtn.png");
	MenuItemSprite* btnPrev = MenuItemSprite::create(prevSprite, prevSprite, prevSprite, this, menu_selector(DeckBuilder::PreviousPage));
	btnPrev->setVisible(true);
	btnPrev->setPositionX(-(winsize.width / 2) + (prevSprite->getContentSize().width)/3);
	menu->addChild(btnPrev);

	Sprite *saveSprite = Sprite::create("btnSaveDeck.png");
	MenuItemSprite* btnSave = MenuItemSprite::create(saveSprite, saveSprite, saveSprite, this, menu_selector(DeckBuilder::saveDeck));
	btnSave->setVisible(true);
	btnSave->setPositionY(-winsize.height / 2 + (saveSprite->getContentSize().height / 2));
	btnSave->setPositionX(saveSprite->getContentSize().width * 0.75);
	menu->addChild(btnSave);

	char str[20];
	sprintf(str, "btnSwitchToP%d.png", 3 - playerID);
	Sprite *switchSprite = Sprite::create(str);
	MenuItemSprite* btnSwitch = MenuItemSprite::create(switchSprite, switchSprite, switchSprite, this, menu_selector(DeckBuilder::switchPlayer));
	btnSwitch->setVisible(true);
	btnSwitch->setPositionY(-winsize.height / 2 + (switchSprite->getContentSize().height / 2));
	btnSwitch->setPositionX(-switchSprite->getContentSize().width * 0.75);
	menu->addChild(btnSwitch);

	sprintf(str, "%d/%d", cardsSelected = 0, maxCards);
	Label* deckNr = Label::createWithTTF(str, "ITCKRIST.TTF", 40);
	deckNr->setPosition(Vec2(winsize.width / 2, winsize.height - prevSprite->getContentSize().height / 3));
	deckNr->setTag(7);
	addChild(deckNr);

	loadDeck();

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

void DeckBuilder::saveDeck(Ref *ref)
{
	char str[15];
	sprintf(str, "Player%d.data", playerID);
	char inputChar;

	FILE * fout = fopen(str, "w");
	for (int i = 0; i < NOCARD; ++i)
	{
		fprintf(fout, "%d", cardsInDeck[i]);
	}
	fprintf(fout, "\n");
	fclose(fout);
}

void DeckBuilder::loadDeck()
{
	char str[15];
	sprintf(str, "Player%d.data", playerID);
	char inputChar;

	FILE * fin = fopen(str, "r");
	if (fin)
	{
		for (int i = 0; i < NOCARD; ++i)
		{
			fscanf(fin, "%c", &inputChar);
			inputChar -= '0';
			cardsInDeck[i] = inputChar;
			cardsSelected += inputChar;
		}
		fprintf(fin, "\n");
		fclose(fin);

		sprintf(str, "%d/%d", cardsSelected, maxCards);
		((Label*)(getChildByTag(7)))->setString(str);
	}
}
void DeckBuilder::switchPlayer(Ref *ref)
{
	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	if (playerID == 1)
	{
		runAction(MoveTo::create(0.5, Vec2(0, winsize.height)));
		twinLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
	}
	else //if (playerID == 2)
	{
		runAction(MoveTo::create(0.5, Vec2(0, -winsize.height)));
		twinLayer->runAction(MoveTo::create(0.5, Vec2(0, 0)));
	}
}
void DeckBuilder::HomeScene(Ref* ref)
{
	Scene* newScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(newScene);
}
