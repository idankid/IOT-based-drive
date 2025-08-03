/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-26
* \ <_. )	@Ex AsyncInjection
*  `---' 	@reviewer Gil		 	 				
************************************************/

#include <iostream>
#include "AsyncInjection.hpp"

bool RunNTimes()
{
	static int count = 0;
	++count;

	std::cout << count << std::endl;
	if(count < 5)
	{
		return true;
	}

	return false;
}

int main()
{
	new ilrd::AsyncInjection(RunNTimes, std::chrono::milliseconds(1000));
	while(getchar() != '\n'){}
	return 0;
}
