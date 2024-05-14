#pragma once

#include "Futex.h"

#include <atomic>
#include <cstdint>

class Mutex {
public:
    void Lock() {
      uint32_t expected = MUTEX_FREE;

      if (futex_block_.compare_exchange_strong(expected, MUTEX_ACQUIRED)) {
        return;
      }

      while (true) {
        expected = MUTEX_ACQUIRED;
        futex_block_.compare_exchange_strong(expected, MUTEX_ACQUIRED_QUEUE);
        if (expected == MUTEX_ACQUIRED || expected == MUTEX_ACQUIRED_QUEUE) {
          FutexWait((int*)&futex_block_, MUTEX_ACQUIRED_QUEUE);
        }

        expected = MUTEX_FREE;
        if (futex_block_.compare_exchange_strong(expected,
                                                 MUTEX_ACQUIRED_QUEUE)) {
          break;
        }
      }
    }

    void Unlock() {
      uint32_t expected = MUTEX_ACQUIRED;
      if (!futex_block_.compare_exchange_strong(expected, MUTEX_FREE)) {
        futex_block_.store(MUTEX_FREE);
        FutexWake((int*)&futex_block_);
      }
    }

  // BasicLockable
  // https://en.cppreference.com/w/cpp/named_req/BasicLockable

    void lock() 
    { Lock(); }

    void unlock() 
    { Unlock(); }

private:
    enum { MUTEX_FREE, MUTEX_ACQUIRED, MUTEX_ACQUIRED_QUEUE };
    std::atomic<uint32_t> futex_block_{MUTEX_FREE};
};
