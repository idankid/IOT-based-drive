/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "waitable_queue.hpp"

namespace ilrd
{

template <typename T, class Q = std::priority_queue<T>>
class PriorityQueue : public WaitableQueue<T, Q>
{
public:
    bool Pop(std::chrono::milliseconds timeout, T& res);
    bool Pop(T& res);
};

template <typename T, class Q>
bool PriorityQueue<T, Q>::Pop(T& res)
{
    std::unique_lock<std::timed_mutex> lock(this->m_lock);

    this->m_cond.wait(lock, [this](){return !this->m_container.empty();});

    res = this->m_container.top();
    this->m_container.pop();

    return true;
}


template <typename T, class Q>
bool PriorityQueue<T, Q>::Pop(std::chrono::milliseconds timeout, T& res)
{
    auto before = std::chrono::high_resolution_clock::now();
    
    std::unique_lock<std::timed_mutex> lock(this->m_lock);
    this->m_lock.try_lock_for(timeout);

    auto after = std::chrono::high_resolution_clock::now();
    
    if(!this->m_cond.wait_for(lock, timeout - (after - before) , [this]()
                                        {
                                            return !this->m_container.empty();
                                        }))
    {
        return false;
    }
    
    res = this->m_container.top();
    this->m_container.pop();

    return true;
}

} // ilrd namespac


#endif /*__PRIORITY_QUEUE_H__*/
