#include "Common.h"
#include "Connection.h"

#include <thread>

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

int Connection::readData(std::string &buffer)
{
	char buff[DEFAULT_BUFFLEN];
	memset(buff, 0, DEFAULT_BUFFLEN);
	recv(fileDescriptor, buff, DEFAULT_BUFFLEN, 0);

	std::string dataReceived(buff, SERVER_COMMAND_LENGHT);

	std::lock_guard<std::mutex> lock_buffer(mutexLockString);
	buffer = buffer + dataReceived;
	return 1;
}

bool Connection::isConnected()
{
	return (fileDescriptor != INVALID_SOCKET);
}

int Connection::closeConnection()
{
	closesocket(fileDescriptor);
	fileDescriptor = INVALID_SOCKET;
	return 0;
}

Connection::Connection(SOCKET fd) : fileDescriptor(fd)
{

}

Connection::~Connection()
{
	//closesocket(fileDescriptor);
}
