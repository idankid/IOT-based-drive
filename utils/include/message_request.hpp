/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_REQUEST_HPP__
#define __MESSAGE_REQUEST_HPP__

#include <memory>
#include "AMessage.hpp"
#include "uid.hpp"

namespace ilrd
{

class AMessageRequest : public AMessage
{
public:
    AMessageRequest() = default;
    AMessageRequest(UID id, uint64_t offset, uint64_t length);
    char* Stringify(char*);
    char* Parse(char*);
    int32_t GetSize();
    virtual int32_t GetClassType() const = 0;
    uint64_t GetLength();
    uint64_t GetOffset();
protected:
    uint64_t m_offset;
    uint64_t m_length;
};

}//namespace ilrd

#endif /*__MESSAGE_REQUEST_HPP__*/
