#pragma once

#include "Errors.h"
#include "Future.h"
#include "Move.h"
#include "SharedState.h"
#include "Sync/LockGuard.h"
#include "../SharedPtr/Src/SharedPtr.hpp"

template <class T>
class Promise
{
public:
    Promise() :
    shared_state_ (MakeShared<SharedState<T>, Expected<T, size_t>>(Unexpected(typeid(NoStateError).hash_code())))
    { }

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

        shared_state_->value = Move(value);
        shared_state_->continue_waiting.NotifyOne();
    }

    // One-shot
    template <class SomeType>
    void SetException(SomeType exception) 
    {
        LockGuard locker(shared_state_->mutex);
        shared_state_->value         = Unexpected(typeid(exception).hash_code());

        shared_state_->set_exception = true;
        shared_state_->continue_waiting.NotifyOne();
    }

    ~Promise() 
    {
        LockGuard locker(shared_state_->mutex);

        shared_state_->value         = Unexpected(typeid(BrokenPromiseError()).hash_code());
        shared_state_->set_exception = true;
        shared_state_->continue_waiting.NotifyOne();
    }

private:
    SharedPtr<SharedState<T>, Owner> shared_state_;
};
