/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-19
* \ <_. )	@Ex Dispatcher
*  `---' 	@reviewer Itai		 	 				
************************************************/
#include <iostream>
#include <Dispastcher.hpp>

class Sub
{
public:
    Sub(int num);
    ~Sub() = default;
    void print(int num);
    void printDead();
public:
    int m_a;
};

Sub::Sub(int num) : m_a(num){}

void Sub::print(int num)
{
    std::cout << "Sub notify" << num <<std::endl;
}

void Sub::printDead()
{
    std::cout << "Sub dead" << m_a <<std::endl;
}

int main()
{

    Sub sub(5);
    ilrd::Dispatcher<int> disp;
    ilrd::Callback<Sub, int> callba(sub, &Sub::print, &Sub::printDead);
    
    disp.Register(&callba);
    disp.Notify(6);

    return 0;
}