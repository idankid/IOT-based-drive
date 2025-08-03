/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __NBD_PROXY_HPP__
#define __NBD_PROXY_HPP__

#include <memory> 
#include <map> 
#include <functional>
#include <mutex>

#include "Dispastcher.hpp"
#include "input_proxy.hpp" /* IInputProxy */
#include "ATaskArgs.hpp"
#include "NBD.hpp"
#include "types.hpp"

namespace ilrd
{

class NBDProxy : public IInputProxy
{
public:
    NBDProxy();
    ~NBDProxy() = default;
    std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, Mode);
    void RegisterForNewTaskArgs(ACallback<ATaskArgs>* callback);

private:
    Dispatcher<ATaskArgs> m_dispatcher;
    std::map<int, std::function<void(std::shared_ptr<ITaskArgs>, 
                                    struct nbd_request, int fd)>> m_fill_funcs;
    std::mutex m_lock;
};
    
}//namespace ilrd

#endif /*__NBD_PROXY_HPP__*/
