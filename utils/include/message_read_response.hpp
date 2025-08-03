/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_READ_RESPONSE_HPP__
#define __MESSAGE_READ_RESPONSE_HPP__

#include <memory>

#include "message_response.hpp"

namespace ilrd
{
class MessageReadResponse : public AMessageResponse
{
public:
    MessageReadResponse() = default;
    MessageReadResponse(UID id, bool status, std::shared_ptr<char[]>, int64_t);
    char* Stringify(char*);
    char* Parse(char*);
    int32_t GetSize();
    int32_t GetClassType() const;
    std::shared_ptr<char[]> GetData() const;
    int64_t GetDataLen() const;
private:
    std::shared_ptr<char[]> m_res;
    int64_t m_len;
};

}//namespace ilrd

#endif /*__MESSAGE_READ_RESPONSE_HPP__*/
