#include <iostream>
#include "Thread.h"
#include "Server.h"

using namespace std;


int main() {
	cout << "hello world!" << endl;
	Server server;
	server.init();
	return 0;
}