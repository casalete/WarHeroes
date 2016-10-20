#include "Common.h"
#include "Connection.h"


std::string Connection::sendData(std::string data)
{
	char buff[100];

	// Send data to client
	data = data + securityStringParse;
	while (data.size() != send(fileDescriptor, data.c_str(), data.size(), 0)) continue;

	int responseSize;
	do{
		responseSize = recv(fileDescriptor, buff, 100, 0);
	} while (strstr(buff + responseSize - strlen(securityStringParse), securityStringParse) != NULL);

	return std::string(buff);
}

Connection::Connection(SOCKET fd) : fileDescriptor(fd)
{

}


Connection::~Connection()
{
	closesocket(fileDescriptor);
}
