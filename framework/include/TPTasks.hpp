/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-10
* \ <_. )	@Ex 
*  `---' 	@reviewer Shani 		 	 				
************************************************/

#ifndef __TPTASKS_H__
#define __TPTASKS_H__

#include <semaphore>

namespace ilrd::thread_pool
{
class ITPTask   
{
public:
    virtual void Run() = 0;
};

template <typename output>
class FutureTask : public ITPTask
{
public:
    FutureTask(std::function<output()> func);
    void Run();
    output out();
private:
    std::binary_semaphore m_sem;
    output m_res;
    std::function<output()> m_func;
};

class FunctionTask : public ITPTask
{
public:
    FunctionTask(std::function<void()> func);
    ~FunctionTask();
    void Run();
private:
    std::function<void()> m_func;
};    

template <typename output>
FutureTask<output>::FutureTask(std::function<output()> func):
m_sem(0), m_func(func)
{}

template <typename output>
void FutureTask<output>::Run()
{
    m_res = m_func();
    m_sem.release();
}

template <typename output>
output FutureTask<output>::out()
{
    m_sem.acquire();
    return m_res;
}
    
} // namespace ilrd::ThreadPool

#endif //__TPTASKS_H__