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

	void doGet(HttpRequest request,HttpResponse response) {
		fstream _file;
		print(request.getHeaders());
		writeHeader(request, response,_file);
		if (!_file)
		{
		}
		
	}

		
	void writeHeader(HttpRequest request, HttpResponse response, fstream &_file) {
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

	void doHead(HttpRequest request, HttpResponse response) {
		fstream _file;
		print(request.getHeaders());
		writeHeader(request, response,_file);
	}

	void doPost(HttpRequest request, HttpResponse response) {

	}

private:

	void print(map<string, string>dataMap) {
		map<string, string>::iterator iter;
		for (iter = dataMap.begin(); iter != dataMap.end(); iter++)
			cout << iter->first << "  "<< iter->second << endl;
	}
};

DefaultHttpProcessor::DefaultHttpProcessor()
{
}

DefaultHttpProcessor::~DefaultHttpProcessor()
{
}

#endif