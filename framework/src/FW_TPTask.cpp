/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework 
*  `---' 	@reviewer Gil		 	 				
************************************************/

#include <functional>           /* std::function */
#include <memory>               /* shared_ptr */
#include <chrono>               /* miliseconds */

#include "handleton.hpp"        /* handleton */
#include "factory.hpp"          /* factory */
#include "logger.hpp"           /* Logger */
#include "command.hpp"          /* ICommand */
#include "AsyncInjection.hpp"   /* asyncInjection */
#include "FW_TPTask.hpp"

ilrd::FW_TPTask::FW_TPTask(std::shared_ptr<ITaskArgs> args) : m_task_arguments(args)
{}

void ilrd::FW_TPTask::Run()
{
    try{

        std::shared_ptr<ICommand> func_to_run = 
        Handleton<Factory<int, ICommand>>::GetInstance()
        ->Create(m_task_arguments->GetKey());
        
        std::pair<std::function<bool(void)>,std::chrono::milliseconds>
        to_inject = func_to_run->Run(m_task_arguments);
        
        if(to_inject.first)
        {
            new AsyncInjection(to_inject.first,to_inject.second);
        }
    }
    catch(const std::exception& e)
    {
        Logger Log;
        Log.Log(std::string("FW_TPTask failed ") + e.what(), Logger::ERROR);
    }
}