/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __FW_TPTASK_HPP__
#define __FW_TPTASK_HPP__

#include "input_proxy.hpp"
#include "TPTasks.hpp"

namespace ilrd
{

class FW_TPTask : public thread_pool::ITPTask
{
public:
    FW_TPTask(std::shared_ptr<ITaskArgs>);
    ~FW_TPTask() = default;
    FW_TPTask(const FW_TPTask& other) = delete;
    void Run();
private:
    std::shared_ptr<ITaskArgs> m_task_arguments;
};

}//namespace ilrd

#endif /*__FW_TPTASK_HPP__*/
