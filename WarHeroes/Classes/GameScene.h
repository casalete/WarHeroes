#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <thread>

#include "cocos2d.h"
#include "Player.h"
#include "ServerConnection.h"

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::Layer* battlefieldLayer;
	Player * player1;
	ServerConnection *server;
	std::string serverCommandBuffer;
	std::mutex mutexReadData;
	std::mutex mutexLockString;
	std::thread * readServerThread;
	


	std::string getDeck(int);

public:
	GameScene();
	~GameScene();
	static GameScene * create();
	//CREATE_FUNC(GameScene); // same as above but macro
	static cocos2d::Scene* createScene();
	virtual bool init();

	void mainLoop(float);
	void processCommands(float);

	int connectServer();
	void receiveData();
	bool isConnected();

	void toMainMenu(Ref *);

};

#endif