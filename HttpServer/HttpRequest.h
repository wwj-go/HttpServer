#pragma once
#include <map>
#include <string>
#include "util.h"

using namespace std;

class HttpRequest
{
public:
	HttpRequest();
	~HttpRequest();

	map<string, string> getParameters() {
		return parameters;
	}

	string getParameter(string key) {
		return parameters[key];
	}

	void addParameter(string name, string value) {
		parameters.insert(pair<string, string>( name, value ));
	}

	map<string,string> getHeaders() {
		return headers;
	}

	string getHeader(string name) {
		return headers[name];
	}

	void addHeader(string name, string value) {
		headers.insert(pair<string, string>(name, value));
	}

	string getRequestLine() {
		return requestLine;
	}

	void setRequestLine(string line) {
		requestLine = line;
		vector<string>vec = split(line, " ");
		method = vec[0];
		vector<string>temp = split(vec[1], "?");
		

		//TODO 获得get参数
		uri = temp[0];
		if (uri.substr(uri.length()-1)=="/")
		{
			uri += "index.html";
		}
		protocol = vec[2];
	}

	string getMethod() {
		return method;
	}

	string getUri() {
		return uri;
	}

	string getProtocol() {
		return protocol;
	}

protected:
	map<string, string>headers;
	map<string, string>parameters;

	string requestLine;
	string method;
	string protocol;
	string uri;

};

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}