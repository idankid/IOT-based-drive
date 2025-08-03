/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include "uid.hpp"

int main()
{
	ilrd::UID id;
	ilrd::UID id2;

	if(id != id)
	{
		std::cout << "is equal failed id == id" << std::endl;
	}
	if(id == id2)
	{
		std::cout << "is equal failed id == id2" << std::endl;
	}
	return 0;
}
