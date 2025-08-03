/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-12
* \ <_. )	@Ex 
*  `---' 	@reviewer Offir Nachshoni	 	 				
************************************************/

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <memory>
#include <functional>
#include <unordered_map>

namespace ilrd
{

template <typename KEY, class BASE, typename ...ARGS>
class Factory
{
public:
    void Register(KEY key, std::function<std::shared_ptr<BASE>(ARGS...)> Creator);
    std::shared_ptr<BASE> Create(KEY key, ARGS...);
    Factory(const Factory& other) = delete;
    Factory() = default;
private:
    void operator=(const Factory& other) = delete;
    std::unordered_map<KEY, std::function<std::shared_ptr<BASE> (ARGS...)>> m_map;
};

template <typename KEY, class BASE, typename ...ARGS>
void Factory<KEY, BASE, ARGS...>::Register(KEY key, std::function<std::shared_ptr<BASE> (ARGS...)> Creator)
{
    m_map[key] = Creator;
}

template <typename KEY, class BASE, typename ...ARGS>
std::shared_ptr<BASE> Factory<KEY, BASE, ARGS...>::Create(KEY key, ARGS... args)
{
    return std::shared_ptr<BASE>(m_map.at(key)(args...));
}

}// namespace ilrd

#endif /*__FACTORY_H__*/
