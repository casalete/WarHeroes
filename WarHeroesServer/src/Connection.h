#ifndef _CONNECTION__H_
#define _CONNECTION__H_

#include <WinSock2.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class Connection
{
private:
	SOCKET fileDescriptor;
public:
	int sendData(std::string);
	Connection(SOCKET);
	~Connection();
};

#endif // !_CONNECTION__H_
