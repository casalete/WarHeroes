#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdio>
#include <string>
#include "ServerConnection.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_BUFLEN 512


int ServerConnection::connectToServer(struct addrinfo *ptr)
{
	// Connect to server.
	int iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		fprintf(stderr, "%d", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		return SOCKET_ERROR;
	}
	return 0;
}

int ServerConnection::sendData(std::string * buffer)
{
	char const *c_buffer = buffer->c_str();
	// Send a simple deck buffer
	int iResult = send(ConnectSocket, c_buffer, buffer->size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	return 0;
}

const char* ServerConnection::receiveData()
{
	memset(buff, 0, DEFAULT_BUFFLEN);
	//int iResult = recv(ConnectSocket, buff, DEFAULT_BUFFLEN, MSG_PEEK);
	//if (iResult)
	//{
		recv(ConnectSocket, buff, DEFAULT_BUFFLEN, 0);
	//}
	return (const char*)buff;
}

int ServerConnection::closeConnection()
{
	int iResult = shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	ConnectSocket = INVALID_SOCKET;
	WSACleanup();
	return iResult;
}

bool ServerConnection::isConnected()
{
	if (ConnectSocket != INVALID_SOCKET)
		return true;
	return false;
}

ServerConnection::ServerConnection()
{

}

ServerConnection::~ServerConnection()
{

}

int ServerConnection::init()
{
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult) {
		fprintf(stderr, "WSAStartup failed: %d\n", iResult);
		return iResult;
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	char buffer[40];
	ZeroMemory(&buffer, sizeof(buffer));
	FILE * fin = fopen("Connection.data", "r");
	if (!fin)
	{
		FILE * fout = fopen("Connection.data", "w");
		fprintf_s(fout, "%s\n%s\n", DEFAULT_PORT, DEFAULT_IP);
		fin = fopen("Connection.data", "r");
	}
	fscanf(fin, "%s\n", buffer);
	char * port = ("" == std::string(buffer)) ? DEFAULT_PORT : buffer;
	fscanf(fin, "%s\n", buffer);
	char * ip = ("" == std::string(buffer)) ? DEFAULT_IP : buffer;

	// Resolve the server address and port
	//iResult = getaddrinfo("www.example.com", "80", &hints, &result);
	iResult = getaddrinfo(ip, port, &hints, &result);
	if (iResult) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return iResult;
	}

	ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	connectToServer(ptr);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	/*
	// -------these lines are just for testing------
	int recvbuflen = DEFAULT_BUFLEN;

	std::string sendbuf = "$0|this is a test|;";
	sendbuf[1] = 1;
	char const *sendbuf1 = sendbuf.c_str();
	//char recvbuf[DEFAULT_BUFLEN];

	iResult = send(ConnectSocket, sendbuf1, sendbuf.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}*/
	// -----if connection works, it's a success------

	//sendData(&std::string("$1|111111111111111111111111111111111111|;"));
	return 0;
}

ServerConnection * ServerConnection::create()
{
	ServerConnection *pRet = new ServerConnection();
	if (pRet && !pRet->init())
	{
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
	return NULL;
}
