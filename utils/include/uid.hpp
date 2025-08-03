/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __UID_HPP__
#define __UID_HPP__

#include <sys/types.h>  	/* pid_t */
#include <chrono> 			/* time, time_t */
#include <atomic>           /* atomic */

namespace ilrd
{
class UID
{
public:
    UID();
    ~UID() = default;
    bool IsBad() const;
    bool operator==(const UID& other);
    size_t GetHash() const;
    char* Stringify(char* buff);
    char* Parse(char* buff);
    int32_t GetSize() const;
private:
    static bool GetIp(char* ip_holder);

    bool m_is_bad;
    std::chrono::system_clock::time_point m_time;
    pid_t m_process_id;
    size_t m_count;
    char m_ip[4];
    static std::atomic<size_t> counter;
};

bool operator<(const UID a, const UID b);

}//namespace ilrd

#endif /*__UID_HPP__*/
