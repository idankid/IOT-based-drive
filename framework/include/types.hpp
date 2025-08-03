/***********************************************
 *     __	@author Idan Kideckel
 * ___( o)>	@date 2025-17-04
 * \ <_. )	@Ex
 *  `---' 	@reviewer
 ************************************************/

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <linux/nbd.h>

namespace ilrd
{
enum Mode : int
{
    READ,
    Write
};

struct Reply
{
    struct nbd_reply rep;
    int fd;
};


} // namespace ilrd

#endif // __TYPES_HPP__