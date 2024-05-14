#pragma once

#include <atomic>
#include <linux/futex.h> 
#include <sys/syscall.h> 
#include <unistd.h>

long futex(uint32_t *uaddr, int futex_op, uint32_t val,
           const struct timespec *timeout,   /* or: uint32_t val2 */
           uint32_t *uaddr2, uint32_t val3)
{
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}

void FutexWait(uint32_t* address, const uint32_t value)
{
    while (true)
    {
        int futex_rc = futex(address, FUTEX_WAIT, value, NULL, NULL, 0);

        if (futex_rc == 0 && *address == value)
            return;
    }
}

void FutexWake(uint32_t* address)
{
    while(true)
    {
        int futex_rc = futex(address, FUTEX_WAKE, 1, NULL, NULL, 0);
        if (futex_rc > 0)
            return;
    }
}