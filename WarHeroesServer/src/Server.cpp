#include "Common.h"
#include "Server.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_IP "127.0.0.1"
#define BUFFER_SIZE 512

int Server::setupSockets()
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	struct addrinfo hints, *servinfo = NULL, *p = NULL;
	//socklen_t sin_size;
	int yes = 1;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//hints.ai_flags = AI_PASSIVE; // use my IP

	iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &servinfo);
	if (iResult != 0) {//TODO check this out
		fprintf(stderr, "getaddrinfo: %s\n", (char*)gai_strerror(iResult));
		WSACleanup();
		return -1;
	}
	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((serverDescriptor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		if (setsockopt(serverDescriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(int)) == -1) {
			perror("setsockopt");
			WSACleanup();
			exit(1);
		}
		if (bind(serverDescriptor, p->ai_addr, p->ai_addrlen) == -1) {
			closesocket(serverDescriptor);
			perror("server: bind");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	freeaddrinfo(servinfo); // all done with this structure

	if (listen(serverDescriptor, 5) == -1) {
		perror("listen");
		return 3;
	}
	return 0;
}

int Server::acceptPlayer(int playerID)
{
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size = sizeof their_addr;
	SOCKET new_fd = INVALID_SOCKET;
	char *buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
	std::string commands = "";
	std::string::iterator iter;
	

	//char s[INET6_ADDRSTRLEN];
	int establishedConnection = 0;
	while (!establishedConnection)
	{

		new_fd = accept(serverDescriptor, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == INVALID_SOCKET) {
			perror("accept");
			continue;
		}
		establishedConnection = 1;
		//inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s); //TODO check this out
		//printf("server: got connection from %s\n", s);
		/*	if (send(new_fd, "Hello, world!", 13, 0) == -1)
		perror("send");
		*/
		int iResult = recv(new_fd, buffer, BUFFER_SIZE, 0);
		/*commands = commands + buffer;
		iter = commands.begin();
		if (*iter == '$')// TODO remove this testing string
		{
			++iter;
			if (*iter == 1) // "$0|this is a test|;" this is the string
				++iter;
			*(iter++ + 15) = 0;
			fprintf(stderr, "%s\n", iter);
			iter += 15;
			if (*iter == ';')
				fprintf(stderr, "Succesfull test!\n");
			commands.erase(commands.begin(), iter+1);
		}

		memset(buffer, 0, BUFFER_SIZE);
		iResult = recv(new_fd, buffer, BUFFER_SIZE, 0);*/
		commands = commands + buffer;
		while (NOCARD + 5 > commands.size()) // 2x|(pipes), 1x;(comma), 1x(command), 1x$
		{
			fprintf(stderr, "%s\n", buffer);
			memset(buffer, 0, BUFFER_SIZE);
			iResult = recv(new_fd, buffer, BUFFER_SIZE, 0);
			commands = commands + buffer;
			continue; // until we have all deck info
		}
			iter = commands.begin();
		*(iter + NOCARD + 3) = 0;
		fprintf(stderr, "%s\n", (commands.c_str()) + 3);
		commands.erase(commands.begin(), commands.begin() + 3);

		_players[playerID] = Player::create(charDecktoVectorDeck((char*)commands.c_str()), new_fd);
	}
	free(buffer);
	return 0;
}

int Server::sendData(int id, std::string &data)
{
	return _players[id]->sendData(data);
}

Server::Server(Player** players) : _players(players)
{
	setupSockets();
}


Server::~Server()
{
	delete (_players[0]);
	delete (_players[1]);
	closesocket(serverDescriptor);
}
