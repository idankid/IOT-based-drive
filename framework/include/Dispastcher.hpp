/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-19
* \ <_. )	@Ex Dispatcher
*  `---' 	@reviewer Itai	 	 				
************************************************/

#ifndef __DISPACHER_HPP__
#define __DISPACHER_HPP__

#include <algorithm>
#include <list>
#include <queue>

namespace ilrd
{
template <typename EVENT>
class ACallback;

/*----------------------- DISPATCHER -------------------------------*/

template <typename EVENT>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();
    void Register(ACallback<EVENT>* callback);
    void Unregister(ACallback<EVENT>* callback);
    void Notify(EVENT event);
private:
    std::list<ACallback<EVENT>*> m_events;
    std::queue<std::pair<bool, ACallback<EVENT>*>> m_waiting_events;
    void emptyWaitingQueue();
};

template <typename EVENT>
void Dispatcher<EVENT>::emptyWaitingQueue()
{
    while(!m_waiting_events.empty())
    {
        std::pair curr = m_waiting_events.front(); 
        if(curr.first)
        {
            m_events.push_back(curr.second);
        }
        else
        {
            m_events.remove(curr.second);
        }

        m_waiting_events.pop();
    }
}

template <typename EVENT>
Dispatcher<EVENT>::~Dispatcher()
{
    emptyWaitingQueue();
    
    std::for_each(m_events.begin(), m_events.end(), 
    [](ACallback<EVENT>* cur)
    {
        cur->NotifyDeath();
    });
}

template <typename EVENT>
void Dispatcher<EVENT>::Register(ACallback<EVENT>* callback)
{
    if(!callback)
    {
        throw std::runtime_error("missing callback");
    }
    callback->SetDispatcher(this);
    m_waiting_events.push(std::make_pair(true, callback));
}

template <typename EVENT>
void Dispatcher<EVENT>::Unregister(ACallback<EVENT>* callback)
{
    if(!callback)
    {
        throw std::runtime_error("missing callback");
    }
    m_waiting_events.push(std::make_pair(false, callback));
}   

template <typename EVENT>
void Dispatcher<EVENT>::Notify(EVENT event)
{
    emptyWaitingQueue();
    
    std::for_each(m_events.begin(), m_events.end(), 
            [&event](ACallback<EVENT>* cur)
            {
                cur->Notify(event);
            });
}

/*----------------------- ACallback ------------------------------*/
template <typename EVENT>
class ACallback
{
public:
    ACallback();
    virtual ~ACallback();
    virtual void Notify(EVENT event) = 0;
    virtual void NotifyDeath();
    void SetDispatcher(Dispatcher<EVENT>* dispatcher);
protected:
    Dispatcher<EVENT>* m_dispacher;
};

template <typename EVENT>
ACallback<EVENT>::ACallback() : m_dispacher(nullptr)
{}

template <typename EVENT>
void ACallback<EVENT>::SetDispatcher(Dispatcher<EVENT>* dispatcher)
{
    m_dispacher = dispatcher;
}

template <typename EVENT>
ACallback<EVENT>::~ACallback()
{
    NotifyDeath();
    if(m_dispacher)
    {
        m_dispacher->Unregister(this);
        m_dispacher = nullptr;
    }
}

template <typename EVENT>
void ACallback<EVENT>::NotifyDeath()
{}

/*-------------------- callback ---------------------------*/
template <class OBJ, typename EVENT>
class Callback : public ACallback<EVENT>
{
public:
    Callback(OBJ& object, void(OBJ::*ptr_to_mem_function)(EVENT), 
            void(OBJ::*ptr_to_notif_delete_functio)() = nullptr);
    ~Callback() = default;
    void Notify(EVENT event);
    virtual void NotifyDeath();

private:
    OBJ& m_obj;
    void (OBJ::*m_notify_func)(EVENT event);
    void (OBJ::*m_death_func)();
};

template <class OBJ, typename EVENT>
void Callback<OBJ, EVENT>::Notify(EVENT event)
{
    (m_obj.*m_notify_func)(event);
}

template <class OBJ, typename EVENT>
Callback<OBJ, EVENT>::Callback(OBJ& obj, void(OBJ::*ptr_to_notify_function)(EVENT),  
void(OBJ::*ptr_to_notify_death_function)()) : m_obj(obj), 
m_notify_func(ptr_to_notify_function), m_death_func(ptr_to_notify_death_function)
{}  

template <class OBJ, typename EVENT>
void Callback<OBJ, EVENT>::NotifyDeath()
{
    this->m_dispacher = nullptr;
    if(m_death_func)
    {
        (m_obj.*m_death_func)();
    }
}

}// ilrd
#endif //__DISPACHER_HPP__
