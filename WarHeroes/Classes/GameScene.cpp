#include "GameScene.h"
#include "Player.h"
USING_NS_CC;


using namespace cocos2d::ui;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	
	Sprite *backgroundSprite = Sprite::create("Battlefield.png");
	addChild(backgroundSprite);
	backgroundSprite->setPosition(Vec2(winsize.width / 2 , winsize.height/2));

	battlefieldLayer = Layer::create(); 
	battlefieldLayer->setPosition(Vec2((winsize.width * 3.0) / 5.0, (winsize.height * 9.0) / 20.0));
	
	


	return true;
}
