#include "GameScene.h"
#include <thread>

#include "Deck.h"
#include "Player.h"
#include "Common.h"
#include "HelloWorldScene.h"


USING_NS_CC;

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
	delete readServerThread;
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
	
	Sprite *backgroundSprite = Sprite::create("Battlefield.png");
	addChild(backgroundSprite);
	backgroundSprite->setPosition(Vec2(winsize.width / 2 , winsize.height/2));

	battlefieldLayer = Layer::create(); 
	battlefieldLayer->setPosition(Vec2((winsize.width * 3.0) / 5.0, (winsize.height * 9.0) / 20.0));

	Scheduler * _scheduler = getScheduler();
	_scheduler->schedule(schedule_selector(GameScene::mainLoop), this, 0, false);

	return true;
}

void GameScene::receiveData() //Thread function
{
	for (int i = 0; i < 100; ++i); // this line is for thread delay No need to make too many recv calls
	//besides, the main thread needs time for the data buffer too

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
	std::string * serverCommand;
	std::lock_guard<std::mutex> * lock_buffer = new std::lock_guard<std::mutex>(mutexLockString);
		for (i = serverCommandBuffer.begin(); i != serverCommandBuffer.end(); ++i)
		{
			if (*i == ';')
				break;
		}
		if (i != serverCommandBuffer.end())
		{
			serverCommand = new std::string(serverCommandBuffer.begin(), ++i);
			serverCommandBuffer.erase(serverCommandBuffer.begin(), i);
		}
		else serverCommand = new std::string();
	delete lock_buffer;


	Sprite *backgroundSprite = Sprite::create("HomeScene.png");
	if (serverCommand->size() == 10)
	{
		switch ((serverCode)(*serverCommand)[1])
		{
		case SEND_SERVER_INIT:
			break;
		case SEND_SERVER_DECK:
			break;
		case SEND_SERVER_STARTGAME:
			addChild(backgroundSprite);
			break;
		case SEND_SERVER_DRAWCARD:
			break;
		case SEND_SERVER_ENDGAME:
			//lock_buffer = new std::lock_guard<std::mutex>(mutexReadData);
			server->closeConnection();
			//delete lock_buffer;
			readServerThread->join();
			toMainMenu(NULL);
			break;
		default:
			break;
		
		}
	} else {
		fprintf(stderr, "Error: bad command from server!\n");
	}
	delete serverCommand;
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

bool GameScene::isConnected()
{
	return server->isConnected();
}


void GameScene::toMainMenu(Ref *ref)
{
	Scene* newScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(newScene);
}