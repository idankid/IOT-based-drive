/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-13
* \ <_. )	@Ex Singleton
*  `---' 	@reviewer Itai	 	 				
************************************************/

#include <iostream>
#include "singleton.hpp"

class Test
{
public:
	void print();
private:
	Test();
	friend class ilrd::Singleton<Test>;
};

Test::Test(){}

void Test::print()
{
	std::cout << "hi" << std::endl;
}
class holla
{
friend class ilrd::Singleton<holla>;
public:
	void print();
private:
	holla();
};

holla::holla(){}

void holla::print()
{
	std::cout << "holla" << std::endl;
}

int main()
{
	ilrd::Singleton<Test>::GetInstance()->print();
	ilrd::Singleton<holla>::GetInstance()->print();
	return 0;
}
