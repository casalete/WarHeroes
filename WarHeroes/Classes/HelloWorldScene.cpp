#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	// BUTON PLAY
	Menu *menu = Menu::create();
	Sprite *playSprite = Sprite::create("btnPlay.png");
	MenuItemSprite* btnPlay = MenuItemSprite::create(playSprite, playSprite, playSprite, this, static_cast<cocos2d::SEL_MenuHandler>(&HelloWorld::Play));
	btnPlay->setVisible(true);
	menu->addChild(btnPlay);
	addChild(menu);
	menu->setPositionX(100.0);
	menu->setPositionY(100.0);

	

    return true;
}
void HelloWorld::Play(Ref *ref)
{
	
}
