#include "Deck.h"
#include "DeckBuilder.h"
#include "cocos2d.h"





 using namespace cocos2d::ui;
using namespace cocos2d;



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

	//Buttons (next & previous)

	Menu *menu = Menu::create();
	Sprite *nextSprite = Sprite::create("nextBtn.png");
	MenuItemSprite* btnNext = MenuItemSprite::create(nextSprite, nextSprite, nextSprite, this, static_cast<cocos2d::SEL_MenuHandler>(&DeckBuilder::NextPage));
	btnNext->setVisible(true);
	menu->addChild(btnNext);
	addChild(menu);
	btnNext->setPositionX((winsize.width / 2) - (nextSprite->getContentSize().width)/3);
	


	Sprite *prevSprite = Sprite::create("prevBtn.png");
	MenuItemSprite* btnPrev = MenuItemSprite::create(prevSprite, prevSprite, prevSprite, this, static_cast<cocos2d::SEL_MenuHandler>(&DeckBuilder::PreviousPage));
	btnPrev->setVisible(true);
	menu->addChild(btnPrev);
	btnPrev->setPositionX(-(winsize.width / 2) + (prevSprite->getContentSize().width)/3);
	




	return true;

}
void DeckBuilder::NextPage(Ref *ref)
{

}
void DeckBuilder::PreviousPage(Ref *ref)
{

}