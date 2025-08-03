/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <dlfcn.h>
#include "DllLoader.hpp"

int main()
{
	ilrd::DllLoader loader;

	loader.Load("+/home/idan/Desktop/git/projects/final_project/framework/liblibs.so");

	return 0;
}
