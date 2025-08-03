/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <cstring>
#include "file_manager.hpp"

int main()
{
    ilrd::FileManager fm("../minion1.dat");

    std::shared_ptr<char[]> to_write(new char[sizeof("hello world")]);
    memcpy(to_write.get(), "hello world", sizeof("hello world"));
    fm.Write(to_write, sizeof("hello world"), 2);

    std::shared_ptr<char[]> to_read(new char[sizeof("hello world")]);
    fm.Read(to_read, 5, 8);

    std::cout<< to_read.get() << std::endl;
    return 0;
}