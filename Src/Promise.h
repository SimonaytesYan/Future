#pragma once

#include "LockGuard.h"
#include "SharedState.h"
#include "../SharedPtr/Src/SharedPtr.hpp"

template <class T>
class Promise
{
public:
    Promise() :
    shared_state_ (std::make_shared<SharedState<T>>(std::unexpected(std::make_exception_ptr(NoStateError()))))
    {
      printf("Promise ctor\n");
    }

    // Non-copyable
    Promise(const Promise&) = delete;
    Promise& operator=(const Promise&) = delete;

    // Movable
    Promise(Promise&& other) = default;
    Promise& operator=(Promise&& other) = default;

    // One-shot
    Future<T> MakeFuture() 
    {
        return Future<T>(shared_state_);
    }

    // One-shot
    // T - movable
    void SetValue(T value) 
    {
        LockGuard locker(shared_state_->mutex);

        shared_state_->value = std::move(value);
        shared_state_->continue_waiting.notify_one();
    }

    // One-shot
    void SetException(std::exception_ptr exception) 
    {
        LockGuard locker(shared_state_->mutex);

        shared_state_->value         = std::unexpected(exception);
        shared_state_->set_exception = true;
        shared_state_->continue_waiting.notify_one();
    }

    ~Promise() 
    {
        std::lock_guard locker(shared_state_->mutex);

        shared_state_->value         = std::unexpected(std::make_exception_ptr(BrokenPromiseError()));
        shared_state_->set_exception = true;
        shared_state_->continue_waiting.notify_one();
    }

private:
    SharedPtr<SharedState<T>> shared_state_;
};
