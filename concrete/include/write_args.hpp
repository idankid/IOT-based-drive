/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __WRITE_ARGS_HPP__
#define __WRITE_ARGS_HPP__

#include <memory>       /* shared_ptr */

#include "ATaskArgs.hpp"

namespace ilrd
{
class WriteArgs : public ATaskArgs
{
public:
	WriteArgs(size_t offset = 0, size_t length = 0);
	WriteArgs(const WriteArgs& other) = delete;
	~WriteArgs();
	int GetKey();
	std::shared_ptr<char[]>& GetBuffer();
	void SetBuffer(std::shared_ptr<char[]>& buffer);
private:
	std::shared_ptr<char[]> m_buffer;
};

}//namespace ilrd

#endif /*__WRITE_ARGS_HPP__*/
