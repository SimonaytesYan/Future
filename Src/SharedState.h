#pragma once

#include <expected>

#include "Sync/Mutex.h"
#include "Sync/Condvar.h"

template <class T>
struct SharedState
{
    SharedState()
    {}

    SharedState(std::expected<T, std::exception_ptr> other_value)
    {
        value = other_value;
    }

    bool set_exception = false;

    std::expected<T, std::exception_ptr> value;
    Mutex                                mutex;
    CondVar                              continue_waiting;
};
