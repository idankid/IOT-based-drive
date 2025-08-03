/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex DirMonitor
*  `---' 	@reviewer Liad		 	 				
************************************************/

#ifndef __DIRMONITOR_HPP__
#define __DIRMONITOR_HPP__

#include <thread>
#include "Dispastcher.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(const std::string& path);
    ~DirMonitor();
    void Register(ACallback<const std::string&>* call);
    void UnRegister(ACallback<const std::string&>* call);
    void Run();
private:
    int InitNotify();
    int InitWatcher();
    void ThreadJob();

    bool m_stop_thread;
    std::thread m_thread;
    std::string m_path;
    int m_notify_fd;
    int m_watcher;
    Dispatcher<const std::string&> m_dispatch;
};
    
        
}// ilrd namespace
#endif /*__DIRMONITOR_HPP__*/