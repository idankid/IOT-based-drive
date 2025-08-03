/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __AMESSAGE_HPP__
#define __AMESSAGE_HPP__

#include <cstddef>

#include "uid.hpp"

namespace ilrd
{

enum MessageType : int32_t
{
    READ_REQUEST,
    WRITE_REQUEST,
    READ_RESPONSE,
    WRITE_RESPOSE
};

class AMessage
{
public:
    AMessage() = default;
    AMessage(UID uid);
    UID GetUID();
    virtual char* Stringify(char*) = 0;
    virtual char* Parse(char*) = 0;
    virtual int32_t GetSize() = 0;
    virtual int32_t GetClassType() const = 0;
private:
    UID m_uid;
};

}//namespace ilrd

#endif /*__AMESSAGE_HPP__*/
