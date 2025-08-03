/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-10
* \ <_. )	@Ex 
*  `---' 	@reviewer Shani 	 				
************************************************/

#include <unistd.h>
#include <iostream>
#include "thread_pool.hpp"

class task1 : public ilrd::thread_pool::ITPTask
{
public:
	void Run(void);
};

void task1::Run(void)
{
	sleep(2);
    std::cout << "Task 1 finished" << std::endl;
}

void task_1(void)
{
	sleep(2);
    std::cout << "Task 1 finished" << std::endl;
}
void task2(void)
{
	sleep(2);
    std::cout << "Task 2 finished" << std::endl;
}

int task_future()
{
	sleep(4);
	return 5;
}

void taskSleep()
{
	sleep(10);
    std::cout << "Finished slow task" << std::endl;
}

void task3(void)
{
	sleep(2);
    std::cout << "Task 3 finished" << std::endl;
}


void TestTasks()
{
	std::shared_ptr<ilrd::thread_pool::ITPTask> one(new task1());
	std::shared_ptr<ilrd::thread_pool::ITPTask> two(new ilrd::thread_pool::FunctionTask(task2));
	std::shared_ptr<ilrd::thread_pool::ITPTask> three(new ilrd::thread_pool::FutureTask<int>(task_future));
	ilrd::ThreadPool pool(4);
	pool.AddTask(one, ilrd::ThreadPool::Priority::LOW);
	pool.AddTask(two, ilrd::ThreadPool::Priority::HIGH);
	pool.AddTask(one, ilrd::ThreadPool::Priority::LOW);
	pool.AddTask(one, ilrd::ThreadPool::Priority::LOW);
	pool.AddTask(three, ilrd::ThreadPool::Priority::LOW);

	int res = static_cast<ilrd::thread_pool::FutureTask<int>*>(three.get())->out();
	std::cout << res << std::endl;
}

void TestPause()
{
	ilrd::ThreadPool pool(4);
	ilrd::thread_pool::FunctionTask* two = new ilrd::thread_pool::FunctionTask(task2);
	std::shared_ptr<ilrd::thread_pool::ITPTask> task_to_add(two);
	pool.Pause();
	
	pool.AddTask(task_to_add); 
	pool.AddTask(task_to_add); 
	std::cout << "after pause" << std::endl;
	sleep(1);

	pool.Resume();

	pool.Pause();
}

void TestNumOfThreads()
{
	ilrd::ThreadPool pool;
	pool.SetNumOfThreads(2);
	sleep(1);
	pool.SetNumOfThreads(6);
}

void TestProirity()
{
    ilrd::ThreadPool pool(4);

    std::shared_ptr<ilrd::thread_pool::ITPTask> func(new ilrd::thread_pool::FunctionTask(taskSleep));
    std::shared_ptr<ilrd::thread_pool::ITPTask> func1(new ilrd::thread_pool::FunctionTask(task_1));
    std::shared_ptr<ilrd::thread_pool::ITPTask> func2(new ilrd::thread_pool::FunctionTask(task2));
    std::shared_ptr<ilrd::thread_pool::ITPTask> func3(new ilrd::thread_pool::FunctionTask(task3));

    for(size_t i = 0; i < 4; ++i)
    {
        pool.AddTask(func, ilrd::ThreadPool::Priority::MID);
    }
    sleep(2);
    for(size_t i = 0; i < 4; ++i)
    {
        pool.AddTask(func1, ilrd::ThreadPool::Priority::HIGH);
        pool.AddTask(func2, ilrd::ThreadPool::Priority::MID);
        pool.AddTask(func3, ilrd::ThreadPool::Priority::LOW);
    }
}


int main()
{
	TestProirity();
	TestTasks();
	TestPause();
	TestNumOfThreads();
	return 0;
}
