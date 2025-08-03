/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_RESPONSE_HPP__
#define __MESSAGE_RESPONSE_HPP__

#include "AMessage.hpp"

namespace ilrd
{
class AMessageResponse : public AMessage
{
public:
    AMessageResponse() = default;
    AMessageResponse(UID id, bool status);
    bool GetStatus() const;
    virtual char* Stringify(char*);
    virtual char* Parse(char*);
    virtual int32_t GetSize();
    virtual int32_t GetClassType() const = 0;
public:
    bool m_status;
};

}//namespace ilrd

#endif /*__MESSAGE_RESPONSE_HPP__*/
