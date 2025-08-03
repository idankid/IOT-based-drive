/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex messaging
*  `---' 	@reviewer 		 	 				
************************************************/

#include <memory>
#include <iostream>
#include <cstring>
#include <iostream>

#include "handleton.hpp"
#include "factory.hpp"
#include "message_read_request.hpp"
#include "message_write_request.hpp"
#include "message_read_response.hpp"
#include "message_write_response.hpp"

std::shared_ptr<ilrd::AMessage> receive(char* buff)
{
    int32_t size = *(int32_t*)buff;
    buff += sizeof(int32_t);
    int32_t class_type = *(int32_t*)buff;
    buff += sizeof(int32_t);
    
    char res_buff[size];
    memcpy(res_buff, buff, size);

    std::shared_ptr<ilrd::AMessage> mesg =  
            ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::
                                            GetInstance()->Create(class_type);
    
    mesg->Parse(res_buff);

    return mesg;
}

void TestReadRequest()
{
    ilrd::UID id1;
    ilrd::MessageReadRequest req(id1, 5, 30);
    char* to_fill = new char[sizeof(req)];
    req.Stringify(to_fill);
    
    std::shared_ptr<ilrd::AMessage> res = receive(to_fill);

    std::cout << res->GetSize() << std::endl;
}

void TestWriteRequiest()
{
    std::shared_ptr<char[]> buffer(new char[30]);
    memcpy(buffer.get(), "hello there", 11);
    ilrd::UID id1;
    ilrd::MessageWriteRequest req(id1, 5, 30, buffer);
    char* to_fill = new char[sizeof(req)];
    req.Stringify(to_fill);
    
    std::shared_ptr<ilrd::AMessage> res = receive(to_fill);

    std::cout << res->GetSize() << std::endl;
}

void TestReadResponse()
{
    std::shared_ptr<char[]> buffer(new char[30]);
    memcpy(buffer.get(), "hello there", 11);
    ilrd::UID id1;
    ilrd::MessageReadResponse req(id1, true, buffer, 30);
    size_t size = req.GetSize();
    char* to_fill = new char[size];
    req.Stringify(to_fill);
    
    std::shared_ptr<ilrd::AMessage> res = receive(to_fill);

    std::cout << res->GetSize() << std::endl;
}

void TestWriteResponse()
{
    ilrd::UID id1;
    ilrd::MessageWriteResponse req(id1, true);
    char* to_fill = new char[sizeof(req)];
    req.Stringify(to_fill);
    
    std::shared_ptr<ilrd::AMessage> res = receive(to_fill);

    std::cout << res->GetSize() << std::endl;
}

std::shared_ptr<ilrd::AMessage> CreateReadRequest()
{
    return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageReadRequest());
}
std::shared_ptr<ilrd::AMessage> CreateWriteRequest()
{
    return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageWriteRequest());
}
std::shared_ptr<ilrd::AMessage> CreateReadResponse()
{
    return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageReadResponse());
}
std::shared_ptr<ilrd::AMessage> CreateWriteResponse()
{
    return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageWriteResponse());
}

int main()
{
    ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
        Register(ilrd::MessageType::READ_REQUEST, CreateReadRequest);
    ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
        Register(ilrd::MessageType::WRITE_REQUEST, CreateWriteRequest);
    ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
        Register(ilrd::MessageType::READ_RESPONSE, CreateReadResponse);
    ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
        Register(ilrd::MessageType::WRITE_RESPOSE, CreateWriteResponse);

    TestReadRequest();
    TestWriteRequiest();
    TestReadResponse();
    TestWriteResponse();
    return 0;
}