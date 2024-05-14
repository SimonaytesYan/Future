#pragma once

template<class Mutex>
class LockGuard
{
public:
    LockGuard(Mutex& mutex) :
    mutex_ (mutex)
    { 
        mutex_.lock();
    }

    LockGuard(const Mutex& mutex) = delete;

    ~LockGuard()
    {
        mutex_.unlock();
    }

private:
    Mutex mutex_;
};