/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/
#include <iostream>
#include <dlfcn.h>
#include "thread_pool.hpp"
#include "handleton.hpp"

void openLib()
{
	void * handler = dlopen("./libfunc.so", RTLD_LAZY);
	if(!handler)
	{
		std::cout << "lib not opened" << std::endl;
		return;
	}

	void* symbol = dlsym(handler, "_Z3funv");
	void (*func)() = reinterpret_cast<void(*)()>(symbol);
	if(!func)
	{
		std::cout << "fun symbol not found" << std::endl;
		return;
	}
	
	func();
	dlclose(handler);
}

int main()
{
	openLib();

	std::cout<< ilrd::Handleton<ilrd::ThreadPool>::GetInstance() <<std::endl;
	return 0;
}
