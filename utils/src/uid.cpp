/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "uid.hpp"

#include <unistd.h> 		/* getpid*/
#include <string.h> 		/* memcmp, memcpy, strcmp */
#include <ifaddrs.h>		/* getifaddrs, freeifaddrs, ifaddrs */
#include <netinet/in.h>		/* sockaddr_in, AF_INET */
#include "uid.hpp"

bool ilrd::UID::GetIp(char* ip_holder)
{
    struct ifaddrs* list;
	struct ifaddrs* curr;
    struct sockaddr_in *sock_address;
    std::atomic<bool> found = false;

    /* getting the list of network interfaces */
    if (getifaddrs(&list) == -1) 
    {
        return false;
    }

    for (curr = list; curr != NULL && !found; curr = curr->ifa_next) 
    {
    	/* AF_INET is ipv4 */
        if (curr->ifa_addr != NULL && curr->ifa_addr->sa_family == AF_INET) 
        {
            sock_address = (struct sockaddr_in *) curr->ifa_addr;
            
            /* getting the the not local host */
            if (strcmp(curr->ifa_name, "lo") != 0)
            {
               	memcpy(ip_holder, &sock_address->sin_addr, 4);
                found = true;
                break;
            }
        }
    }
    
    freeifaddrs(list);
    
    if(!found)
    {
    	return false;
    }

	return true;
}

std::atomic<size_t> ilrd::UID::counter = 0;

ilrd::UID::UID() : m_time(std::chrono::system_clock::now()),
    m_process_id(getpid()), m_count(counter++)
{
    m_is_bad = !GetIp(m_ip);
}

bool ilrd::UID::IsBad() const
{
    return m_is_bad;
}

bool ilrd::UID::operator==(const UID& other)
{
    bool time = this->m_time == other.m_time;
    bool counting = this->m_count == other.m_count;
    bool pid = this->m_process_id == other.m_process_id;
    bool ip =  memcmp(this->m_ip, other.m_ip, 4);

    return time && counting && pid && !ip;
}

size_t ilrd::UID::GetHash() const
{
    return std::chrono::system_clock::to_time_t(m_time) / (m_count + m_process_id);
}

bool ilrd::operator<(const ilrd::UID a, const ilrd::UID b)
{
    return a.GetHash() < b.GetHash();
}

char* ilrd::UID::Stringify(char* buff)
{
    *(time_t*)buff = std::chrono::system_clock::to_time_t(m_time);
    buff += sizeof(time_t);

    *(size_t*)buff = m_count;
    buff += sizeof(size_t);

    *(pid_t*)buff = m_process_id;
    buff += sizeof(pid_t);

    memcpy(buff, m_ip, 4);
    buff += 4;

    return buff;
}

char* ilrd::UID::Parse(char* buff)
{
    time_t time_val = *(time_t*)buff;
    m_time = std::chrono::system_clock::from_time_t(time_val);
    buff += sizeof(time_t);

    m_count = *(size_t*)buff;
    buff += sizeof(size_t);

    m_process_id = *(pid_t*)buff;
    buff += sizeof(pid_t);

    memcpy(m_ip, buff, 4);
    buff += 4;

    return buff;
}

int32_t ilrd::UID::GetSize() const
{
    return sizeof(time_t) + sizeof(m_count) +
            sizeof(m_process_id) + sizeof(m_ip);
} 