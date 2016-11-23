#include "Common.h"
#include "Connection.h"


int Connection::sendData(std::string data)
{
	//char buff[100];

	// Send data to client
	//data = data + securityStringParse;
	//while (data.size() != send(fileDescriptor, data.c_str(), data.size(), 0)) continue;
	send(fileDescriptor, data.c_str(), data.size(), 0);
	//int responseSize;
	//do{
	//	responseSize = recv(fileDescriptor, buff, 100, 0);
	//} while (strstr(buff + responseSize - strlen(securityStringParse), securityStringParse) != NULL);

	//return std::string(buff);
	return 0;
}

Connection::Connection(SOCKET fd) : fileDescriptor(fd)
{

}


Connection::~Connection()
{
	closesocket(fileDescriptor);
}
