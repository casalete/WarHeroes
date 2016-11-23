#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "DeckBuilder.h"
#include "GameScene.h"

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

	// BUTTONS
	Menu *menu = Menu::create();
	MenuItemImage *btnDeck = MenuItemImage::create("deckBuilderBtn.png", "deckBuilderBtn.png", "deckBuilderBtn.png", CC_CALLBACK_1(HelloWorld::deckBuilder, this));
	btnDeck->setVisible(true);
	//btnPlay->setScale(3); // ca sa pot sa te vad mai bine! no need am dioptriile 0
	menu->addChild(btnDeck);
	addChild(menu);
	menu->setPositionX(btnDeck->getContentSize().width);
	menu->setPositionY(winsize.height- btnDeck->getContentSize().height);

	MenuItemImage *btnPlay = MenuItemImage::create("btnPlay.png", "btnPlay.png", "btnPlay.png", CC_CALLBACK_1(HelloWorld::Play, this));
	btnPlay->setVisible(true);
	//btnPlay->setScale(3); // ca sa pot sa te vad mai bine! no need am dioptriile 0
	menu->addChild(btnPlay);
	addChild(menu);
	//btnPlay->setPositionX(btnDeck->getContentSize().width);
	btnPlay->setPositionY(- btnDeck->getContentSize().height -20.0 -btnPlay->getContentSize().height);

    return true;
}
void HelloWorld::deckBuilder(Ref *ref)
{
	Scene* newScene = DeckBuilder::createScene();
	Director::getInstance()->replaceScene(newScene);
}
void HelloWorld::Play(Ref *ref)
{
	Scene* newScene = GameScene::createScene();
	if (newScene)
		Director::getInstance()->replaceScene(newScene);
	else 
		fprintf_s(stdout, "Error: GameScene could not start");
}

