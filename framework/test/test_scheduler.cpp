/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-25
* \ <_. )	@Ex Scheduler 
*  `---' 	@reviewer Liad	 	 				
************************************************/

#include <unistd.h>
#include <iostream>
#include <functional> 

#include <handleton.hpp>

#include "scheduler.hpp"

class Task : public ilrd::ISchedulerTask
{
public:
	Task(std::function<void(void)> func);
	~Task() = default;
	void Run();
private:
	std::function<void(void)> m_func;
};

Task::Task(std::function<void(void)> func) : m_func(func)
{}

void Task::Run()
{
	m_func();
}

void func1()
{
	std::cout << "func 1" << std::endl;
}

void func2()
{
	std::cout << "func 2" << std::endl;
}

void func3()
{
	std::cout << "func 3" << std::endl;
}

void sleepTask()
{
	std::cout << "sleep task" << std::endl;
	sleep(2);
}

void TestEalierTask()
{
	ilrd::Scheduler* sched = ilrd::Handleton<ilrd::Scheduler>::GetInstance();

	std::shared_ptr<ilrd::ISchedulerTask> task1(new Task(func1));
	std::shared_ptr<ilrd::ISchedulerTask> task2(new Task(func2));
	std::shared_ptr<ilrd::ISchedulerTask> task3(new Task(func3));

	sched->AddTask(task2, std::chrono::milliseconds(3000));
	sched->AddTask(task1, std::chrono::milliseconds(1000));
	sleep(1);
	sched->AddTask(task3, std::chrono::milliseconds(5000));
}

void TestFinished()
{
	ilrd::Scheduler* sched = ilrd::Handleton<ilrd::Scheduler>::GetInstance();

	std::shared_ptr<ilrd::ISchedulerTask> task1(new Task(func1));
	std::shared_ptr<ilrd::ISchedulerTask> task2(new Task(func2));
	std::shared_ptr<ilrd::ISchedulerTask> task3(new Task(func3));

	sched->AddTask(task1, std::chrono::milliseconds(1000));
	sched->AddTask(task3, std::chrono::milliseconds(10000));
	sleep(1);
	sched->AddTask(task2, std::chrono::milliseconds(5000));
}

void TestPassedTime()
{
	ilrd::Scheduler* sched = ilrd::Handleton<ilrd::Scheduler>::GetInstance();

	std::shared_ptr<ilrd::ISchedulerTask> task1(new Task(func1));
	std::shared_ptr<ilrd::ISchedulerTask> taskSleep(new Task(sleepTask));

	sched->AddTask(taskSleep, std::chrono::milliseconds(1000));
	sleep(1);
	sched->AddTask(task1, std::chrono::milliseconds(500));
}

int main()
{
	std::cout << "===========Earlier Test==========" << std::endl;
	TestEalierTask();
	sleep(10);
	
	std::cout << "===========Finished Test==========" << std::endl;
	TestFinished();
	sleep(10);
	
	std::cout << "===========Time Passed Test==========" << std::endl;
	TestPassedTime();

	return 0;
}
