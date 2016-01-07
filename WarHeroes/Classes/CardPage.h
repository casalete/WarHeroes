#ifndef __CARD_PAGE_H__
#define __CARD_PAGE_H__
#include "cocos2d.h"

using namespace cocos2d::ui;

class CardPage : public cocos2d::Layer
{
private:
	int pageNumber;
	CardPage(int i) : Layer(), pageNumber(i){};
public:
	virtual bool init();
	static CardPage* create(int i);
};



#endif //__CARD_PAGE_H_