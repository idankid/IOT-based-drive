/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MINION_READ_ARGS_HPP__
#define __MINION_READ_ARGS_HPP__

#include <memory>

#include "master_proxy.hpp"
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
    MasterProxy* GetProxy();
	void SetProxy(MasterProxy*);
private:
	MasterProxy* m_prox;
};

}//namespace ilrd

#endif /*__MINION_READ_ARGS_HPP__*/
