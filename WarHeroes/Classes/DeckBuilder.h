#ifndef __DECK_BUILDER_H__
#define __DECK_BUILDER_H__
#include "cocos2d.h"

using namespace cocos2d::ui;

class DeckBuilder : public cocos2d::Layer
{
public:


	int pageNumber;

	static cocos2d::Scene* createScene();
	virtual bool init();
	void NextPage(Ref *);
	void PreviousPage(Ref *);
	CREATE_FUNC(DeckBuilder);
};



#endif