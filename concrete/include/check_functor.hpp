/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-23
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __CHECK_FUNCTOR_HPP__
#define __CHECK_FUNCTOR_HPP__

#include <chrono>
#include "uid.hpp"

namespace ilrd
{

class CheckFunctor
{
public:
    CheckFunctor(UID id);
    bool operator()();
private:
    UID m_uid;
    std::chrono::system_clock::time_point m_start;
};

}//namespace ilrd

#endif /*__CHECK_FUNCTOR_HPP__*/
