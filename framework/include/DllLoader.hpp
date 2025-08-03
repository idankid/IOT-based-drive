/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex 
*  `---' 	@reviewer Liad		 	 				
************************************************/

#ifndef __DLLLOADER_H__
#define __DLLLOADER_H__

#include <string>
#include <unordered_map>

typedef void* DLL_HANDLER;

namespace ilrd
{
class DllLoader
{
public:
    DllLoader() = default;
    ~DllLoader();
    void Load(const std::string& path);
private:
    void closeLib(const std::string& path);
    std::unordered_map<std::string, DLL_HANDLER> m_libs;
};

}//namspace ilrd

#endif /*__DLLLOADER_H__*/
