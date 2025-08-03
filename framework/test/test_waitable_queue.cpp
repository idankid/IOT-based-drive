/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <mutex>
#include <thread>
#include <iostream>
#include "priority_queue.hpp"
#include "waitable_queue.hpp"

std::mutex lock;
typedef struct
{
	ilrd::WaitableQueue<size_t>* que;
	size_t data;
}data_t;

void* JobPush(void* data_)
{
	size_t data = ((data_t*)data_)->data;
	(((data_t*)data_)->que)->Push(data);
	
	lock.lock();
	std::cout << "pushed " << data << std::endl;
	lock.unlock();
	return NULL;
}

void* JobPop(void* data_)
{
	size_t data;
	(((data_t*)data_)->que)->Pop(data);
	
	lock.lock();
	std::cout << "popped " << data << std::endl;
	lock.unlock();
	return NULL;
}

void testThreads()
{
	const int thread_num = 20;
	ilrd::WaitableQueue<size_t> q;

	std::thread threads[thread_num];
	data_t data[thread_num];
	for(int i = 0; i < thread_num; ++i)
	{
		data[i].que = &q;
		data[i].data = i;
	}

	for(int i = 0; i < 5; ++i)
	{
		threads[i] = std::thread(JobPop, &data[i]);
	}
	
	for(int i = 0; i < 10; ++i)
	{
		threads[i + 5] = std::thread(JobPush, &data[i + 5]);
	}
		
	for(int i = 0; i < 5; ++i)
	{
		threads[i + 15] = std::thread(JobPop, &data[i + 15]);
	}

	for(int i = 0; i < thread_num; ++i)
	{
		threads[i].join();
	}
}

void TestWait()
{
	size_t res;
	ilrd::WaitableQueue<size_t> q;
	while(!q.Pop((std::chrono::milliseconds)2000, res))
	{
		std::cout << "timeout" << std::endl;
		q.Push(6);
	}

	std::cout << "waited for" << res << std::endl;
}

void testPriority()
{
	ilrd::PriorityQueue<size_t, std::priority_queue<size_t>> q;
	q.Push(5);
	q.Push(3);
	q.Push(1);
	q.Push(9);
	for(int i = 0; i < 4; ++i)
	{
		size_t res;
		q.Pop(res);
		std::cout << res << std::endl;
	}

}

int main()
{

	// testThreads();
	TestWait();
	// testPriority();
	return 0;
}
