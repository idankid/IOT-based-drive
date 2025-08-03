/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __READ_ARGS_HPP__
#define __READ_ARGS_HPP__

#include "ATaskArgs.hpp"

namespace ilrd
{

class ReadArgs : public ATaskArgs
{
public:
	ReadArgs(size_t offset = 0, size_t length = 0);
	ReadArgs(const ReadArgs& other) = delete;
	~ReadArgs() = default;
	int GetKey();
private:
};

}//namespace ilrd

#endif /*__READ_ARGS_HPP__*/
