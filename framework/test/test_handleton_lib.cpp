#include <iostream>
#include "handleton.hpp"
#include "thread_pool.hpp"

void fun()
{
    std::cout << ilrd::Handleton<ilrd::ThreadPool>::GetInstance() << std::endl;
}
