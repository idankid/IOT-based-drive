/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MASTER_PROXY_HPP__
#define __MASTER_PROXY_HPP__

#include <mutex>
#include <map>
#include <functional>

#include "types.hpp"
#include "input_proxy.hpp"
#include "UDPSocket.hpp"
#include "ATaskArgs.hpp"
#include "AMessage.hpp"

#define BINDING_PORT 12345

namespace ilrd
{
class MasterProxy : public IInputProxy
{
public:
    MasterProxy(int port = BINDING_PORT);
    ~MasterProxy() = default;
    std::shared_ptr<ilrd::ITaskArgs> GetTaskArgs(int fd, Mode mode);
    void SendReadResponse(UID id, bool status,
                                std::shared_ptr<char[]> buffer, int64_t len);
    void SendWriteResponse(UID id, bool status);
    int GetFd();
private:
    void InitFactories();
    UDPSocket m_master;
    std::mutex m_lock;
    std::map<int32_t, std::function<void(std::shared_ptr<ITaskArgs>,
         std::shared_ptr<ilrd::AMessage>)>> m_fill_funcs;
};

}//namespace ilrd

#endif /*__MASTER_PROXY_HPP__*/
