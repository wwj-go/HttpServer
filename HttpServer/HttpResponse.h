#pragma once
#include <map>
#include <string>
#include "HttpRequest.h"

using namespace std;

class HttpResponse:HttpRequest 
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
		string temp="HTTP/1.1 200 OK\r\n";
		map<string, string>::iterator iter;
		for (iter = headers.begin(); iter != headers.end(); iter++) {
			temp.append(iter->first + ":" + iter->second+"\r\n");
		}
		temp.append("\r\n");
		send(conn,temp.c_str(), temp.length(), 0);
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