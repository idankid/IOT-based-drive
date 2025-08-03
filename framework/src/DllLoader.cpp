/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex 
*  `---' 	@reviewer Liad		 	 				
************************************************/

#include <dlfcn.h>  /*dlopen, dlclose*/
#include <algorithm> /* foreach */

#include "DllLoader.hpp"

ilrd::DllLoader::~DllLoader()
{
    std::for_each(m_libs.begin(), m_libs.end(), 
    [](std::pair<std::string, DLL_HANDLER> curr){
        dlclose(curr.second);
    });
}

void ilrd::DllLoader::closeLib(const std::string& path)
{
    dlclose(m_libs[path]);
    m_libs.erase(path);
}

void ilrd::DllLoader::Load(const std::string& path)
{
    char sign = path[0];
    std::string file_name = path.substr(1);
    switch(sign)
    {
        case '+':
            if(m_libs[file_name])
            {
                closeLib(file_name);
            }
            try
            {
                DLL_HANDLER handler = dlopen(file_name.c_str(), RTLD_LAZY);
                if(handler == nullptr)
                {
                    throw std::runtime_error("failed to open dll");
                }

                m_libs[file_name] = handler;
            }
            catch(...)
            {
                throw;
            }
            break;
        case '-':
            closeLib(file_name);
            break;
    }
}