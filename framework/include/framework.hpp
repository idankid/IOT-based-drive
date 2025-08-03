/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __FRAMEWORK_HPP__
#define __FRAMEWORK_HPP__

#include <vector>     /* vector */
#include <string>   /* string */
#include <memory>   /* shared_ptr */

#include "DirMonitor.hpp"   /* Dir_monitor */
#include "DllLoader.hpp"    /* DllLoader */
#include "types.hpp"
#include "command.hpp"
#include "input_proxy.hpp"

namespace ilrd
{
 
class Framework
{
public:
    struct CallbackListItem
    {
        CallbackListItem(int, Mode, IInputProxy*);
        int m_fd;
        Mode m_mode;
        IInputProxy* m_input_proxy;
    };
    
    struct FactoryListItem
    {
        FactoryListItem(int key, 
            std::function<std::shared_ptr<ilrd::ICommand>(void)> factory_func);
        int m_key;
        std::function<std::shared_ptr<ilrd::ICommand>()> m_factory_func;
    };

    /*
        @description constructor
        @param callback - a vector of fds and modes and their callbacks
        @param plugin_path - the path to the plugin folder
        @param factory_init - a vector to initialize the factory with
    */
    Framework(const std::vector<CallbackListItem>& callbacks,
            const std::string& plugin_path, 
            const std::vector<FactoryListItem>& factory_init);
    
    /*
        @description - destructor
    */
    ~Framework() = default;

    /*
        @description - runs the framework (it is blocking)
    */
    void Run(); //blocking
private:
    void InitReactor(const std::vector<CallbackListItem>& callbacks);
    void InitFactory(const std::vector<FactoryListItem>& factory_init);

    DirMonitor m_moniter;
    DllLoader m_loader;
    Callback<DllLoader, const std::string&> m_callback;
};

}//namespace ilrd

#endif /*__FRAMEWORK_HPP__*/
