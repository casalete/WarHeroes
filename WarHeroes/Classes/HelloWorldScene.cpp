#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "DeckBuilder.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
	
	Sprite *backgroundSprite = Sprite::create("HomeScene.png");
    addChild(backgroundSprite);

	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	backgroundSprite->setScaleX(winsize.width / backgroundSprite->getContentSize().width);
	backgroundSprite->setScaleY(winsize.height / backgroundSprite->getContentSize().height);
	backgroundSprite->setPosition(winsize.width / 2.0, winsize.height / 2.0);

	// BUTON PLAY
	Menu *menu = Menu::create();
	Sprite *deckBuilder = Sprite::create("deckBuilderBtn.png");
	MenuItemSprite* btnPlay = MenuItemSprite::create(deckBuilder, deckBuilder, deckBuilder, this, menu_selector(HelloWorld::deckBuilder));
	btnPlay->setVisible(true);
	//btnPlay->setScale(3); // ca sa pot sa te vad mai bine! no need am dioptriile 0
	menu->addChild(btnPlay);
	addChild(menu);
	menu->setPositionX(btnPlay->getContentSize().width);
	menu->setPositionY(winsize.height- btnPlay->getContentSize().height);

    return true;
}
void HelloWorld::deckBuilder(Ref *ref)
{
	Scene* newScene = DeckBuilder::createScene();
	Director::getInstance()->replaceScene(newScene);
}
