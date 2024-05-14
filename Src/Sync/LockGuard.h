#pragma once

template<class MutexT>
class LockGuard
{
public:
    LockGuard(MutexT& new_mutex) :
    mutex_ (new_mutex)
    { 
        mutex_.lock();
    }

    LockGuard(const MutexT& new_mutex) = delete;

    ~LockGuard()
    {
        mutex_.unlock();
    }

private:
    MutexT& mutex_;
};