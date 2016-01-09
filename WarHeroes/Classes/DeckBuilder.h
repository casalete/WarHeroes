#ifndef __DECK_BUILDER_H__
#define __DECK_BUILDER_H__
#include "cocos2d.h"
#include "CardPage.h"
#include "Deck.h"

using namespace cocos2d::ui;

class DeckBuilder : public cocos2d::Layer
{
private:
	CardPage * previousPage;
	CardPage * curentPage;
	CardPage * nextPage;
	int pageNumber;
	int cardsInDeck[(int)NOCARD];
	int cardsSelected;

	int playerID;
	DeckBuilder* twinLayer;
	DeckBuilder(int i) : Layer(), playerID(i){};
public:
	int modifyCardOccurrence(int, int);
	int getCardOccurrence(int);

	static cocos2d::Scene* createScene();
	void NextPage(Ref *);
	void PreviousPage(Ref *);
	void saveDeck(Ref *);
	void loadDeck();
	void switchPlayer(Ref *);
	void HomeScene(Ref *);

	static DeckBuilder* create(int);
	void createTwin();
	void setTwin(DeckBuilder*);
	virtual bool init();

};

#endif