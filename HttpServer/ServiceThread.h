#pragma once
#ifndef SERVICE_THREAD_H
#define SERVICE_THREAD_H


#include "Thread.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "DefaultHttpProcessor.h"
#include "util.h"
#include "Server.h"

class ServiceThread : public Thread
{
public:


	ServiceThread(int conn) {
		this->conn = conn;
	}

	~ServiceThread() {
		int a = 1;
		cout << "123" << a<<endl;
	}
	


	void run()
	{
		try
		{
			read();
			parse();
			dispatch();
		}
		catch (const std::exception)
		{
			close(conn);
		}
		close(conn);
	}

	void dispatch() {
		if (request.getMethod() == "GET")
		{
			processor.doGet(request, response);
		}
		if (request.getMethod() == "HEAD")
		{
			processor.doHead(request, response);
		}
		if (request.getMethod() == "POST")
		{
			processor.doPost(request, response);
		}
	}

	void read() {
		while (true)
		{
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			printf("%s", buffer);
			int len = recv(conn, buffer, sizeof(buffer), 0);
			if (len <= 0)
			{
				break;
			}
			requestStr.append(buffer);
			if (requestStr.find("\r\n\r\n") != -1)
				break;
		}
	}

	//存在一定问题
	void parse() {
		vector<string>vec = split(requestStr, "\r\n");
		request.setRequestLine(vec[0]);
		for (int i = 1; i < vec.size(); i++)
		{
			vector<string>header = split(vec[i], ":");
			if (header.size() < 2)
				continue;
			request.addHeader(header[0], header[1]);
		}
	}


private:
	int conn;
	HttpRequest request;
	HttpResponse response;
	DefaultHttpProcessor processor;
	string requestStr;
};

#endif // !SERVICE_THREAD_H
