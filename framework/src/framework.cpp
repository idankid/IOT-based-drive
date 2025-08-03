/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil 		 	 				
************************************************/

#include <algorithm>    /* for_each */

#include "Reactor.hpp"          /* Reactor*/
#include "linux_listener.hpp"   /* LinuxListener*/
#include "DllLoader.hpp"        /* DLLloader */
#include "DirMonitor.hpp"       /* Dirmonitor */
#include "handleton.hpp"        /* handleton */
#include "factory.hpp"          /* factory */
#include "FW_TPTask.hpp"        /* FW_TPTask */
#include "thread_pool.hpp"      /* ThreadPool */

#include "framework.hpp"

/*----------------------- Framework  --------------------------------*/
ilrd::Framework::Framework(
        const std::vector<CallbackListItem>& callbacks, 
        const std::string& plugin_path, 
        const std::vector<FactoryListItem>& factory_init): 
    
        m_moniter(plugin_path), m_callback(m_loader, &ilrd::DllLoader::Load)
{
    InitFactory(factory_init);

    // plugin monitoring
	m_moniter.Register(reinterpret_cast<ACallback<const std::string&>*>(&m_callback));

    InitReactor(callbacks);
}

void ilrd::Framework::Run()
{
	m_moniter.Run();
    Handleton<Reactor>::GetInstance()->Run();
}

void ilrd::Framework::InitFactory(const std::vector<FactoryListItem>& factory_init)
{
    std::for_each(factory_init.begin(), factory_init.end(),
    [](FactoryListItem item)
    {
        Handleton<Factory<int, ICommand>>::GetInstance()
                            ->Register(item.m_key, item.m_factory_func);
    }
);
}

void ilrd::Framework::InitReactor(const std::vector<CallbackListItem>& callbacks)
{
    std::for_each(callbacks.begin(), callbacks.end(), 
        [this](CallbackListItem item)
        {
            Handleton<Reactor>::GetInstance()->Register(item.m_fd, item.m_mode, 
                [item](int fd, ilrd::Mode mode)
                {
                    std::shared_ptr<ITaskArgs> args = item.m_input_proxy->
                                            GetTaskArgs(fd, mode);
                    if(args.get())
                    {
                        std::shared_ptr<FW_TPTask> task(new FW_TPTask(args));
                        Handleton<ThreadPool>::GetInstance()->AddTask(task);
                    }
                });   
            }
        );
}

/*----------------------- List Item classes --------------------------------*/
ilrd::Framework::CallbackListItem::CallbackListItem(
    int fd, 
    Mode mode, 
    IInputProxy* input_proxy
) : m_fd(fd), m_mode(mode), m_input_proxy(input_proxy)
{}

ilrd::Framework::FactoryListItem::FactoryListItem(
    int key, 
    std::function<std::shared_ptr<ilrd::ICommand>()> factory_func)
: m_key(key), m_factory_func(factory_func)
{}