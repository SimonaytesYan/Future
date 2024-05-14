#pragma once

#include "Futex.h"
#include <cstdint>

class CondVar 
{
public:
    template <class Mutex>
    void Wait(Mutex& mutex) 
    {
        if (waiters_.fetch_add(1) == 0) 
            wakeup_.store(NO);
        mutex.unlock();

        FutexWait((uint32_t*)&wakeup_, NO);

        mutex.lock();
        waiters_.fetch_add(-1);
    }

    void NotifyOne() 
    {
        int waiters_number = waiters_.load();
        if (waiters_number != 0) 
        {
            wakeup_.store(NOTIFY);
            FutexWake((uint32_t*)&wakeup_);
        }
    }

    void NotifyAll() 
    {
        int waiters_number = waiters_.load();
        if (waiters_number != 0) 
        {
            wakeup_.store(NOTIFY);
            FutexWake((uint32_t*)&wakeup_);
        }
    }

 private:
    enum 
    {
        NO,
        NOTIFY,
    };

    std::atomic<uint32_t> wakeup_{0};
    std::atomic<uint32_t> waiters_{0};
};
