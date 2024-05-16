#pragma once

#include <expected>

#include "Sync/Mutex.h"
#include "Sync/Condvar.h"

template <class T>
struct SharedState
{
    SharedState()
    {}

    SharedState(Expected<T, size_t> other_value) :
    value (other_value)
    { }

    bool set_exception = false;

    Expected<T, size_t>  value;                 // <value type, hash_code of exception code>
    Mutex                mutex;
    CondVar              continue_waiting;
};
