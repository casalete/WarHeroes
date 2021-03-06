#include "GameScene.h"
#include <thread>

#include "Deck.h"
#include "Player.h"
#include "Common.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define POSITION_ERR 50

using namespace cocos2d::ui;

void readThreadLoop(GameScene * game)
{
	while (game->isConnected())// todo make it stop from a toggle.
	{
		game->receiveData();
	}
}


GameScene::GameScene() : cocos2d::Layer()
{
}

GameScene::~GameScene()
{
	_eventDispatcher->removeEventListener(listener);
	if (server) {
		server->closeConnection();
		readServerThread->join();
		delete readServerThread;// for some reason I get sigfault... do I not need to del thread?
	}
	delete server;
}

GameScene* GameScene::create()
{
	GameScene *pRet = new(std::nothrow) GameScene();
    if (pRet && pRet->connectServer() && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	if (!layer)
	{
		return NULL;
	}

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
int GameScene::connectServer()
{
	server = ServerConnection::create();
	if (!server)
	{
		return NULL;
	}
	return 1;
}


bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	serverCommandBuffer = "";
	selectedCard = NULL;

	server->sendData(&getDeck(1));
	readServerThread = new std::thread(readThreadLoop, this);

	cocos2d::Size winsize = Director::getInstance()->getWinSize();
	positionMiddle = Vec2((winsize.width * 3.0) / 5.0, (winsize.height * 11.0) / 20.0);
	
	Sprite *backgroundSprite = Sprite::create("BattlefieldBG.jpg");
	addChild(backgroundSprite);
	backgroundSprite->setPosition(Vec2(winsize.width / 2 , winsize.height/2));
	Sprite *battlefieldSprite = Sprite::create("gamelayer battlefield.png");
	addChild(battlefieldSprite);
	battlefieldSprite->setPosition(Vec2(winsize.width / 2, winsize.height / 2));

	battlefieldLayer = Layer::create(); 
	battlefieldLayer->setPosition(positionMiddle);
	addChild(battlefieldLayer);

	Scheduler * _scheduler = getScheduler();
	_scheduler->schedule(schedule_selector(GameScene::mainLoop), this, 0, false);

	char str[15];
	//sprintf(str, "card_s_%d.png", KNIGHT);
	sprintf(str, "card%d.png", NOCARD);
	//sprintf(str, "card%d.png", /*pageNumber * 8 +*/ i); // the lines above is for debug
	Sprite *cardZoom = Sprite::create(str);//TODO : change it into class Card
	cardZoom->setPosition(Vec2(winsize.width / 10.0, winsize.height / 2.0));
	addChild(cardZoom, 5, NOCARD);

	listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMoved, this);
	listener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseClick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 10);

	for (int i = 0; i < TOTAL_SOLDIERS_BATTLEFIELD; ++i)
	{
		Card * card = Card::create(NOCARD);
		card->setScale(0.5);
		card->setPosition(getSoldierPosition(i));
		card->setSlot(i);
		battlefieldLayer->addChild(card);
		SoldierSlots.push_back(card);
	}

	return true;
}

void GameScene::receiveData() //Thread function
{
	//for (int i = 0; i < 100; ++i); // this line is for thread delay No need to make too many recv calls
	//besides, the main thread needs time for the data buffer too
	// Now that I looked again, that is stupid :P

	//std::lock_guard<std::mutex> * lock_server = new std::lock_guard<std::mutex>(mutexReadData);
	
	std::string dataReceived = server->receiveData();
	//delete lock_server;

	std::lock_guard<std::mutex> lock_buffer(mutexLockString);
		serverCommandBuffer = serverCommandBuffer + dataReceived;
}

void GameScene::mainLoop(float dt)
{
	processCommands(dt);
}

void GameScene::processCommands(float dt)
{
	//Multi-threading - linile astea iau un std::string cu o comanda de la server
	std::string::iterator i;
	std::string serverCommand = "";
	std::lock_guard<std::mutex> * lock_buffer = new std::lock_guard<std::mutex>(mutexLockString);
		for (i = serverCommandBuffer.begin(); i != serverCommandBuffer.end(); ++i)
		{
			if (*i == ';')
				break;
		}
		if (i != serverCommandBuffer.end())
		{
			serverCommand = serverCommandBuffer.substr(0, ++i - serverCommandBuffer.begin());
			serverCommandBuffer.erase(serverCommandBuffer.begin(), i);
		}
	delete lock_buffer;


	Sprite *backgroundSprite = Sprite::create("HomeScene.png");
	int playerID;
	cardName card;
	Card * playedCard;
	Vec2 pos;
	if (serverCommand.size() == SERVER_COMMAND_LENGHT)
	{
		switch ((serverCode)serverCommand[1])
		{
		case SEND_SERVER_INIT:
			break;
		case SEND_SERVER_DECK:
			break;
		case SEND_SERVER_STARTGAME:
			//addChild(backgroundSprite);
			break;
		case SEND_SERVER_DRAWCARD:
			playerID = serverCommand[2];
			card = (cardName)( (serverCommand[3] << 8) | serverCommand[4] );
			drawCard(playerID, card);
			break;
		case SEND_SERVER_ENDGAME:
			//lock_buffer = new std::lock_guard<std::mutex>(mutexReadData);
			toMainMenu(NULL);
			break;
		case SEND_SERVER_FADECARD:
			if (serverCommand[3])
				playerHand[serverCommand[2]]->enterScroll();
			else
				playerHand[serverCommand[2]]->exitScroll();
			break;
		case SEND_SERVER_PLAYCARD:

			// remove from hand
			playedCard = playerHand[serverCommand[2]];
			for (int i = 0; i < playerHand.size(); ++i)
			{
				Action * shiftCards;
				if (i < serverCommand[2])
				{
					shiftCards = MoveBy::create(0.5, Vec2(playedCard->getContentSize().width / 4.0, 0));
					playerHand[i]->runAction(shiftCards);
				}
				else if (i > serverCommand[2])
				{
					shiftCards = MoveBy::create(0.5, Vec2(-playedCard->getContentSize().width / 4.0, 0));
					playerHand[i]->runAction(shiftCards);
					playerHand[i]->setSlot(i - 1);
				}
			}
			playerHand.erase(playerHand.begin() + serverCommand[2]);

			// identify new place
			pos = getSoldierPosition(serverCommand[3]);

			// move it on battlefield
			playedCard->moveScroll(pos);
			SoldierSlots[serverCommand[3]]->removeFromParent();
			SoldierSlots[serverCommand[3]] = playedCard;
			playedCard->setSlot(serverCommand[3]);
			if ((serverCommand[3] < MY_GUARD_1) || ((serverCommand[3] > MY_GUARD_MANA) && (serverCommand[3] < HIS_GUARD_1)))
			{
				playedCard->setRole(ROLE_WARRIOR);
			} else {
				playedCard->setRole(ROLE_GUARDIAN);
			}
			
			break;
		default:
			break;
		
		}
	} else {
		fprintf(stderr, "Error: bad command from server!\n");
	}
}


int GameScene::drawCard(int playerID, cardName cardID)
{
	Card * card = Card::create(cardID);
	card->setScale(0.5);
	card->setPosition(Vec2(playerHand.size() * card->getContentSize().width / 4.0, -card->getContentSize().height *1.5 - POSITION_ERR));
	card->setSlot(playerHand.size());
	card->setRole(ROLE_INHAND);
	//card->setVisible(false);
	for (int i = 0; i < playerHand.size(); ++i)
	{
		Action * shiftCards = MoveBy::create(0.5, Vec2( -card->getContentSize().width / 4.0, 0));
		playerHand[i]->runAction(shiftCards);
	}
	FiniteTimeAction * bringCard = MoveBy::create(0.5, Vec2(0, card->getContentSize().height / 2.0));
	//FiniteTimeAction * toggleVisibility = ToggleVisibility::create();
	//card->runAction( Sequence::createWithTwoActions(bringCard, toggleVisibility) );
	card->runAction(bringCard);
	battlefieldLayer->addChild(card);
	playerHand.push_back(card);
	return 0;
}

std::string GameScene::getDeck(int playerID)
{
	std::string deck;

	char str[15];
	sprintf(str, "Player%d.data", playerID);

	//char Buffer[NOCARD + 2];
	char* Buffer = (char*)calloc(NOCARD + 2, sizeof(char));

	FILE * fin = fopen(str, "r");
	if (fin)
	{
		fscanf(fin, "%s", Buffer);
		deck = "$1|" + std::string(Buffer) + "|;";
	}

	fclose(fin);
	free(Buffer);
	return deck;
}

cocos2d::Vec2 GameScene::getSoldierPosition(unsigned char soldier)
{
	Vec2 pos;
	cocos2d::Size cardSize = ((Sprite*)getChildByTag(NOCARD))->getContentSize();
	switch ((SoldiersPosition)soldier)
	{
	case MY_WAR_1:
		pos.set(-cardSize.width * 2.25, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_WAR_2:
		pos.set(-cardSize.width * 1.25, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_WAR_3:
		pos.set(-cardSize.width * 0.75, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_WAR_4:
		pos.set(cardSize.width * 0.75, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_WAR_5:
		pos.set(cardSize.width * 1.25, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_WAR_6:
		pos.set(cardSize.width * 2.25, -cardSize.height *0.25 - POSITION_ERR* 0.6);
		break;
	case MY_GUARD_1:
		pos.set(-cardSize.width * 0.25, -cardSize.height *0.5 - POSITION_ERR* 0.6);
		break;
	case MY_GUARD_2:
		pos.set(cardSize.width * 0.25, -cardSize.height *0.5 - POSITION_ERR* 0.6);
		break;
	case MY_GUARD_GOLD:
		pos.set(-cardSize.width * 1.75, -cardSize.height *0.5 - POSITION_ERR* 0.6);
		break;
	case MY_GUARD_MANA:
		pos.set(cardSize.width * 1.75, -cardSize.height *0.5 - POSITION_ERR* 0.6);
		break;
	case HIS_WAR_1:
		pos.set(-cardSize.width * 2.25, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_WAR_2:
		pos.set(-cardSize.width * 1.25, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_WAR_3:
		pos.set(-cardSize.width * 0.75, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_WAR_4:
		pos.set(cardSize.width * 0.75, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_WAR_5:
		pos.set(cardSize.width * 1.25, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_WAR_6:
		pos.set(cardSize.width * 2.25, cardSize.height *0.25 + POSITION_ERR* 0.6);
		break;
	case HIS_GUARD_1:
		pos.set(-cardSize.width * 0.25, cardSize.height *0.5 + POSITION_ERR* 0.6);
		break;
	case HIS_GUARD_2:
		pos.set(cardSize.width * 0.25, cardSize.height *0.5 + POSITION_ERR* 0.6);
		break;
	case HIS_GUARD_GOLD:
		pos.set(-cardSize.width * 1.75, cardSize.height *0.5 + POSITION_ERR* 0.6);
		break;
	case HIS_GUARD_MANA:
		pos.set(cardSize.width * 1.75, cardSize.height *0.5 + POSITION_ERR* 0.6);
		break;
	default:
		break;
	}
	return pos;
}

void GameScene::onMouseMoved(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	//Vec2 pos = Vec2(e->getLocation().x + positionMiddle.x, e->getLocation().y + positionMiddle.y);
	Vec2 pos = Vec2(positionMiddle, Vec2(e->getCursorX(), e->getCursorY()));
	
	if (!selectedCard)
	{
		cardName zoomCard = NOCARD;
		for (int i = 0; i < playerHand.size(); ++i)
		{
			if (playerHand[i]->isMouseOver(pos))
			{
				zoomCard = playerHand[i]->getCardID();
			}
		}

		for (int i = 0; i < SoldierSlots.size(); ++i)
		{
			if (SoldierSlots[i]->isMouseOver(pos))
			{
				zoomCard = SoldierSlots[i]->getCardID();
			}
		}

		char str[15];
		//sprintf(str, "card_s_%d.png", KNIGHT);
		sprintf(str, "card%d.png", zoomCard);
		((Sprite*)getChildByTag(NOCARD))->setTexture(str);
		//TODO: make a Card::clone(zoomCard) function
	}
}


void GameScene::onMouseClick(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	//Vec2 pos = Vec2(e->getLocation().x + positionMiddle.x, e->getLocation().y + positionMiddle.y);
	Vec2 pos = Vec2(positionMiddle, Vec2(e->getCursorX(), e->getCursorY()));
	log("coord on click are: %f %f", pos.x, pos.y);

	Card* selCard = NULL;
	cardName zoomCard = NOCARD;
	int index;
	for (int i = 0; i < playerHand.size(); ++i)
	{
		if (playerHand[i]->isMouseOver(pos))
		{
			selCard = playerHand[i];
			break;
		}
	}
	for (int i = 0; i < SoldierSlots.size(); ++i)
	{
		if (SoldierSlots[i]->isMouseOver(pos))
		{
			index = i;
			selCard = SoldierSlots[i];
			break;
		}
	}

	if (selectedCard)// that means we use selectedCard on selCard if we can
	{
		selectedCard->runAction(ScaleTo::create(0.05, 0.5));
		char str[15];
		//sprintf(str, "card%d.png", NOCARD);
		//((Sprite*)getChildByTag(NOCARD))->setTexture(str);
		//TODO: make a Card::clone(zoomCard) function

		if ((selectedCard->getRole() == ROLE_INHAND) && selCard && (selCard->getCardID() == NOCARD))
		{
			std::string data(SERVER_COMMAND_LENGHT, 0);
			data[0] = '$';
			data[1] = SEND_SERVER_PLAYCARD;
			data[2] = selectedCard->getSlot();
			data[3] = selCard->getSlot();
			data[SERVER_COMMAND_LENGHT - 1] = ';';
			server->sendData(&data);
		}

		selectedCard = NULL;
	} else if (selCard && selCard->getCardID() != NOCARD) {
		selectedCard = selCard;
		if (selCard)
		{
		selectedCard->runAction(ScaleTo::create(0.05, 0.55));
		}
	}
}

bool GameScene::isConnected()
{
	return server->isConnected();
}


void GameScene::toMainMenu(Ref *ref)
{
	Scene* newScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(newScene);
}