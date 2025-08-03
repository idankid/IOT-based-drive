/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex Reactor
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __REACTOR_HPP__
#define __REACTOR_HPP__

#include <map> /* std::map*/
#include <functional>   /* std::function */
#include <memory>       /* shared_ptr */

#include "Listener.hpp"
#include "linux_listener.hpp"

namespace ilrd
{
class Reactor
{
public:
    Reactor(std::shared_ptr<IListener> listener = std::make_shared<LinuxListener>());
    ~Reactor() = default;
    void Register(int fd, Mode, std::function<void(int, Mode)>);
    void UnRegister(int fd, Mode mode);
    void Run(); // blocking
    void Stop();
private:
    std::shared_ptr<IListener> m_listener;
    bool m_is_running;
    std::map<std::pair<int, Mode>,
         std::function<void(int, Mode)>> m_callbacks;
};

} // namespace ilrd


#endif /*__REACTOR_HPP__*/
