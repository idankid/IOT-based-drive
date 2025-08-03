/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __ATASKARGS_HPP__
#define __ATASKARGS_HPP__

#include "input_proxy.hpp"
#include "uid.hpp"

namespace ilrd
{
class ATaskArgs : public ITaskArgs
{
public:
    ATaskArgs(size_t offset, size_t length);
    ~ATaskArgs() = default;
    virtual int GetKey() = 0;
    UID GetUid() const;
    size_t GetLength();
	size_t GetOffset();
    void SetUID(UID id);
	void SetLength(size_t length);
	void SetOffset(size_t offset);
private:
    UID m_uid;
    size_t m_offset;
	size_t m_length;
};

}//namespace ilrd

#endif /*__ATASKARGS_HPP__*/
