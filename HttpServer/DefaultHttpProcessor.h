#pragma once

#ifndef DEFAULT_HTTP_PROCESSOR_H
#define DEFAULT_HTTP_PROCESSOR_H
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <iostream>
#include <fstream>

using namespace std;
string webRoot = "/root/test";

class DefaultHttpProcessor
{
public:
	DefaultHttpProcessor();
	~DefaultHttpProcessor();

	void doGet(HttpRequest request, HttpResponse response) {
		fstream _file;
		print(request.getHeaders());
		writeHeader(request, response, _file);
		if (_file)
		{
			response. writeBody(_file);
			_file.close();
		}
	}


	void doHead(HttpRequest request, HttpResponse response) {
		fstream _file;
		print(request.getHeaders());

		writeHeader(request, response, _file);
		if (_file)
			_file.close();
	}

	void doPost(HttpRequest request, HttpResponse response) {
		print(request.getHeaders());

	}

private:

	void writeHeader(HttpRequest request, HttpResponse response, fstream &_file) {
		/*string uri = request.getUri();
		string lastChar = uri.substr(uri.length() - 1);
		if (lastChar=="/")
		{
			_file = ;
			return;
		}*/

		_file.open(webRoot + request.getUri(), ios::in);
		if (!_file)
		{
			response.write404();
		}
		else
		{
			response.writeHeaders();
		}
	}

	void print(map<string, string>dataMap) {
		map<string, string>::iterator iter;
		for (iter = dataMap.begin(); iter != dataMap.end(); iter++)
			cout << iter->first << "  " << iter->second << endl;
	}
};

DefaultHttpProcessor::DefaultHttpProcessor()
{
}

DefaultHttpProcessor::~DefaultHttpProcessor()
{
}

#endif