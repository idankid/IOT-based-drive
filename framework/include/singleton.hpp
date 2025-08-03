/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-13
* \ <_. )	@Ex Singleton
*  `---' 	@reviewer Itai 	 				
************************************************/

#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <mutex>    /* std::mutex */
#include <atomic>   /* atomic */

namespace ilrd
{
template <typename T>
class Singleton
{
public:
    static T* GetInstance();
    
private:
    static void DeleteInstance();
    Singleton() = delete;
    Singleton(const Singleton<T>& other) = delete;
    ~Singleton() = delete;

    static std::mutex m_lock;
    static std::atomic<T*> m_instance;
};

template <typename T>
std::mutex Singleton<T>::m_lock;

template <typename T>
std::atomic<T*> Singleton<T>::m_instance{nullptr};

template <typename T>
T* Singleton<T>::GetInstance()
{
    if(!m_instance.load(std::memory_order_relaxed))
    {
        std::unique_lock lock(m_lock);
        if(!m_instance.load(std::memory_order_relaxed))
        {
            T* temp = new T;
            std::atexit(Singleton<T>::DeleteInstance);
            m_instance.store(temp, std::memory_order_release);
        }
    }

    return m_instance.load(std::memory_order_relaxed);
}

template <typename T>
void Singleton<T>::DeleteInstance()
{
    delete Singleton<T>::m_instance;
    Singleton<T>::m_instance = (T*)0xDEAD;
}

}//ilrd  
#endif /*__SINGLETON_HPP__*/
