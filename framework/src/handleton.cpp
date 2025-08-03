/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#define __REAL_IMPLEMENTATION_HANDLETON__

#include <memory>
#include "handleton.hpp"
#include "thread_pool.hpp"
#include "scheduler.hpp"
#include "logger.hpp"
#include "factory.hpp"
#include "command.hpp"
#include "input_proxy.hpp"
#include "minion_manager.hpp"
#include "response_manager.hpp"
#include "i_response.hpp"
#include "AMessage.hpp"
#include "file_manager.hpp"
#include "Reactor.hpp"
#include "ticket.hpp"

template class ilrd::Handleton<ilrd::ThreadPool>;
template class ilrd::Handleton<ilrd::Scheduler>;
template class ilrd::Handleton<ilrd::Factory<int, ilrd::ICommand>>;
template class ilrd::Handleton<ilrd::Factory<int, ilrd::ITaskArgs>>;
template class ilrd::Handleton<ilrd::Factory<int, ilrd::IResponse>>;
template class ilrd::Handleton<ilrd::MinionManager>;
template class ilrd::Handleton<ilrd::ResponseManager>;
template class ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>;
template class ilrd::Handleton<ilrd::FileManager>;
template class ilrd::Handleton<ilrd::Reactor>;
template class ilrd::Handleton<ilrd::Factory<int32_t, ilrd::TaskResult, std::shared_ptr<ilrd::AMessage>>>;