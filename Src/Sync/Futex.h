#pragma once

#include <atomic>
#include <linux/futex.h> 
#include <sys/syscall.h> 
#include <unistd.h>

void FutexWait(int* address, const uint32_t value)
{
    while (true)
    {
        int futex_rc = futex(address, FUTEX_WAIT, value, NULL, NULL, 0);

        if (futex_rc == 0 && *address == value)
            return;
    }
}

void FutexWake(int* address)
{
    while(true)
    {
        int futex_rc = futex(address, FUTEX_WAKE, 1, NULL, NULL, 0);
        if (futex_rc > 0)
            return;
    }
}