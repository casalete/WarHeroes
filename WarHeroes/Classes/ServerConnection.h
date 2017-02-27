#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <iphlpapi.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFFLEN 512


class ServerConnection {
private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	int connectToServer(struct addrinfo*);
	int init();

	char buff[DEFAULT_BUFFLEN];
public:
	int sendData(std::string*);
	std::string receiveData();
	int closeConnection();
	bool isConnected();
	ServerConnection();
	~ServerConnection();

	static ServerConnection * create();
};

