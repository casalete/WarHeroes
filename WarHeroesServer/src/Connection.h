#ifndef _CONNECTION__H_
#define _CONNECTION__H_

#include <WinSock2.h>
#include <string>
#include <mutex>


#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFFLEN 512

class Connection
{
private:
	SOCKET fileDescriptor;
public:

	std::mutex mutexLockString;

	int sendData(std::string);
	int readData(std::string &);
	bool isConnected();
	int closeConnection();

	Connection(SOCKET);
	~Connection();
};

#endif // !_CONNECTION__H_
