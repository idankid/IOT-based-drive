/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MINION_PROXY_HPP__
#define __MINION_PROXY_HPP__

#include <mutex>

#include "ATaskArgs.hpp"
#include "types.hpp"
#include "i_minion_proxy.hpp"
#include "waitable_queue.hpp"
#include "AMessage.hpp"
#include "UDPSocket.hpp"

namespace ilrd
{
class MinionProxy : public IMinionProxy
{
public:
    MinionProxy(const char* ip, int port);
    ~MinionProxy();
    void AddWriteTask(UID id, size_t offset, size_t length, std::shared_ptr<char[]> data);
    void AddReadTask(UID id, size_t offset, size_t length);
    int GetMinionFD();
    void OnMinionWake(int fd, Mode mode);

private:
    void Send(std::shared_ptr<AMessage>);
    const char* m_ip;
    int m_port;
    UDPSocket m_minion;
    WaitableQueue<std::shared_ptr<ATaskArgs>> m_args_to_send;
    std::mutex m_lock;
};

}//namespace ilrd

#endif /*__MINION_PROXY_HPP__*/
