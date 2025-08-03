/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MINION_WRITE_ARGS_HPP__
#define __MINION_WRITE_ARGS_HPP__

#include <memory> 
#include "master_proxy.hpp"
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
    void SetBuffer(std::shared_ptr<char[]> buffer);
    MasterProxy* GetProxy();
    void SetProxy(MasterProxy* prox);
private:
    std::shared_ptr<char[]> m_buffer;
    MasterProxy* m_prox;
};
}//namespace ilrd

#endif /*__MINION_WRITE_ARGS_HPP__*/
