#pragma once
#ifndef THREAD_H  
#define THREAD_H  
#include <iostream>  
#include <pthread.h>  

using namespace std;

class Thread
{
private:
	//当前线程的线程ID  
	pthread_t tid;
	//线程的状态  
	int threadStatus;
	//获取执行方法的指针  
	static void * thread_proxy_func(void * args);
	//内部执行方法  
	void* run1();
public:
	//线程的状态－新建  
	static const int THREAD_STATUS_NEW = 0;
	//线程的状态－正在运行  
	static const int THREAD_STATUS_RUNNING = 1;
	//线程的状态－运行结束  
	static const int THREAD_STATUS_EXIT = -1;
	//构造函数  
	Thread();
	//线程的运行实体  
	virtual void run() = 0;
	//开始执行线程  
	bool start();
	//获取线程ID  
	pthread_t getThreadID();
	//获取线程状态  
	int getState();
	//等待线程直至退出  
	void join();

	void detach();
};


//class DefaultThread:Thread
//{
//public:
//	DefaultThread();
//	~DefaultThread();
//
//private:
//
//};
//
//DefaultThread::DefaultThread()
//{
//}
//
//DefaultThread::~DefaultThread()
//{
//}
#endif  
