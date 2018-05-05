#pragma once
#include <map>
#include <string>
#include "HttpRequest.h"
#include <iostream>
#include <fstream>
#include <signal.h>

using namespace std;

class HttpResponse :public HttpRequest
{
public:
	HttpResponse();
	~HttpResponse();

	void setConn(int fid) {
		this->conn = fid;
	}

	void setResponseLine(string responseLine) {
		this->responseLine = responseLine;
	}

	string getResponseLine() {
		return responseLine;
	}

	void write404() {
		send(conn, _404.c_str(), _404.length(), 0);
	}

	void writeHeaders() {
		signal(SIGPIPE, SIG_IGN);
		string temp = "HTTP/1.1 200 OK\r\n";
		map<string, string>::iterator iter;
		for (iter = headers.begin(); iter != headers.end(); iter++) {
			temp.append(iter->first + ":" + iter->second + "\r\n");
		}
		temp.append("\r\n");
		send(conn, temp.c_str(), temp.length(), 0);
	}

	void writeBody(fstream &_file) {
		char buf[1024];
		while (true)
		{
			signal(SIGPIPE, SIG_IGN);
			memset(buf, sizeof(buf), 0);
			_file.read(buf, sizeof(buf));
			int len = _file.gcount();
			if (len <= 0)
				break;

			if (send(conn, buf, len, 0) == -1)
			{
				break;
			}
		}
	}

private:
	string responseLine;
	int conn;
	string _404 = "HTTP/1.1 404 Not Found\r\nContent-Type:text/html\r\nServer:my_server\r\n\r\n<h1>404 Not Found</h1>";
};

HttpResponse::HttpResponse()
{
}

HttpResponse::~HttpResponse()
{
}