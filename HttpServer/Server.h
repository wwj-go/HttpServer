#pragma once
#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <string>
#include "ServiceThread.h"
#include <vector>

using namespace std;
class Server
{
public:
	Server();
	~Server();

	void init(int port) {
		int ss = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in server_sockaddr;
		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_port = htons(port);
		server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		unsigned int value = 0x1;
		setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, (void *)&value, sizeof(value));

		if (bind(ss, (struct sockaddr*) &server_sockaddr, sizeof(server_sockaddr)) == -1) {
			perror("bind error");
			exit(1);
		}
		if (listen(ss, 20) == -1) {
			perror("listen error");
			exit(1);
		}
		this->loop(ss);
	}

	void init() {
		init(80);
	}

private:
	vector<ServiceThread*> serviceThreads;

	void loop(int ss) {
		struct sockaddr_in client_addr;
		socklen_t length = sizeof(client_addr);
		int conn;
		while (true)
		{
			int a = 1;
			conn = accept(ss, (struct sockaddr*)&client_addr, &length);
			if (conn < 0) {
				// TODO 异常处理
				perror("connect error");
			}
			service(conn);
		}
		close(ss);
	}

	void service(int conn) {
		tryRelease();
		ServiceThread *serviceThread = new ServiceThread(conn);
		serviceThreads.push_back(serviceThread);
		serviceThread->start();
		serviceThread->detach();
	}

	void tryRelease() {
		int size = serviceThreads.size();
		for (int i = 0; i < size; i++) {
			if (serviceThreads[i]->getState()==-1)
			{
				delete serviceThreads[i];
				serviceThreads[i] = NULL;
				serviceThreads.erase(serviceThreads.begin() + i);
				i--;
				size--;
			}
		}
	}
};


Server::Server()
{
}

Server::~Server()
{
}
#endif