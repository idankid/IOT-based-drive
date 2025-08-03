/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer Liad		 	 				
************************************************/

#include <mutex>    /* std::mutex */
#include <atomic>   /* atomic */

namespace ilrd
{
#ifdef __REAL_IMPLEMENTATION_HANDLETON__
template <typename T>
class Handleton
{
public:
    static T* GetInstance();
    
private:
    static void DeleteInstance();
    Handleton() = delete;
    Handleton(const Handleton<T>& other) = delete;
    ~Handleton() = delete;

    static std::mutex m_lock;
    static std::atomic<T*> m_instance;
};

template <typename T>
std::mutex Handleton<T>::m_lock;

template <typename T>
std::atomic<T*> Handleton<T>::m_instance{nullptr};

template <typename T>
T* Handleton<T>::GetInstance()
{
    if(!m_instance.load(std::memory_order_relaxed))
    {
        std::unique_lock lock(m_lock);
        if(!m_instance.load(std::memory_order_relaxed))
        {
            T* temp = new T;
            std::atexit(Handleton<T>::DeleteInstance);
            m_instance.store(temp, std::memory_order_release);
        }
    }

    return m_instance.load(std::memory_order_relaxed);
}

template <typename T>
void Handleton<T>::DeleteInstance()
{
    delete Handleton<T>::m_instance;
    Handleton<T>::m_instance = (T*)0xDEAD;
}
#else

template <typename T>
class Handleton
{
public:
    static T* GetInstance();
};


#endif /*__REAL_IMPLEMENTATION_HANDLETON__*/
}//ilrd  

