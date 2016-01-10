#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::Layer* battlefieldLayer;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif