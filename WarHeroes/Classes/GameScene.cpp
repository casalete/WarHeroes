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

	/*char buff[512];
	memset(buff, 0, DEFAULT_BUFFLEN);
	int iResult = recv(ConnectSocket, buff, DEFAULT_BUFFLEN, 0);*/
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
	sprintf(str, "card%d.png", NOCARD);
	//sprintf(str, "card%d.png", /*pageNumber * 8 +*/ i); // the line above is for debug
	Sprite *cardZoom = Sprite::create(str);//TODO : change it into class Card
	cardZoom->setPosition(Vec2(winsize.width / 10.0, winsize.height / 2.0));
	addChild(cardZoom, 5, NOCARD);

	listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMoved, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 10);

	return true;
}

void GameScene::receiveData() //Thread function
{
	for (int i = 0; i < 100; ++i); // this line is for thread delay No need to make too many recv calls
	//besides, the main thread needs time for the data buffer too

	//std::lock_guard<std::mutex> * lock_server = new std::lock_guard<std::mutex>(mutexReadData);
	std::string dataReceived(server->receiveData(), SERVER_COMMAND_LENGHT);
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
	if (serverCommand.size() == SERVER_COMMAND_LENGHT)
	{
		switch ((serverCode)serverCommand[1])
		{
		case SEND_SERVER_INIT:
			break;
		case SEND_SERVER_DECK:
			break;
		case SEND_SERVER_STARTGAME:
			addChild(backgroundSprite);
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

	char Buffer[NOCARD + 2];

	FILE * fin = fopen(str, "r");
	if (fin)
	{
		fscanf(fin, "%s", Buffer);
		deck = "$1|" + std::string(Buffer) + "|;";
	}

	fclose(fin);
	return deck;
}

void GameScene::onMouseMoved(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	//Vec2 pos = Vec2(e->getLocation().x + positionMiddle.x, e->getLocation().y + positionMiddle.y);
	Vec2 pos = Vec2(positionMiddle, Vec2(e->getCursorX(), e->getCursorY()));
	
	cardName zoomCard = NOCARD;
	for (int i = 0; i < playerHand.size(); ++i)
	{
		if (playerHand[i]->isMouseOver(pos))
		{
			zoomCard = playerHand[i]->getCardID();
		}
	}
	char str[15];
	sprintf(str, "card%d.png", zoomCard);
	((Sprite*)getChildByTag(NOCARD))->setTexture(str);
	//TODO: make a Card::clone(zoomCard) function
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