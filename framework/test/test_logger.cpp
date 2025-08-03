/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <thread>		//

#include "logger.hpp"

void ErrorJob(ilrd::Logger* logger)
{
	logger->Log("this is from ERROR thread", ilrd::Logger::ERROR);
}

void WarningJob(ilrd::Logger* logger)
{
	logger->Log("this is from Warning thread", ilrd::Logger::WARNING);
}

void InfoJob(ilrd::Logger* logger)
{
	logger->Log("this is from INFO thread", ilrd::Logger::INFO);
}

int main()
{
	ilrd::Logger logger;

	std::thread t1(&ErrorJob, &logger);
	std::thread t2(&WarningJob, &logger);
	std::thread t3(&InfoJob, &logger);

	ilrd::Logger log2("../logger");
	log2.Log("hello there");

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
