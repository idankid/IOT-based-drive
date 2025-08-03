/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_WRITE_REQUEST_HPP__
#define __MESSAGE_WRITE_REQUEST_HPP__

#include <memory>
#include "message_request.hpp"

namespace ilrd
{
class MessageWriteRequest : public AMessageRequest
{
public:
    MessageWriteRequest() = default;
    MessageWriteRequest(UID id, uint64_t offset, uint64_t length,
                         std::shared_ptr<char[]> buffer);
    char* Stringify(char*);
    char* Parse(char*);
    int32_t GetSize();
    int32_t GetClassType() const;
    std::shared_ptr<char[]> GetBuffer();
private:
    std::shared_ptr<char[]> m_buffer;
};


}//namespace ilrd

#endif /*__MESSAGE_WRITE_REQUEST_HPP__*/
