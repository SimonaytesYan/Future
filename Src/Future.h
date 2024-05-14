#pragma once

#include "Errors.h"
#include "Move.h"
#include "SharedState.h"
#include "Sync/Condvar.h"
#include "Sync/LockGuard.h"
#include "../SharedPtr/Src/SharedPtr.hpp"

template <class T>
class Future
{

    template <typename U>
    friend class Promise;

public:
    // Non-copyable
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;

    // Movable
    Future(Future&& other) = default;
    Future& operator=(Future&& other) = default;

    // One-shot
    T Get() 
    {
        LockGuard lock_guard(shared_state_->mutex);
        while (ContinueWaiting())
            shared_state_->continue_waiting.Wait(shared_state_->mutex);

        if (shared_state_->value.has_value())
        {
            T object(Move(shared_state_->value.value()));
            shared_state_->value = std::unexpected(std::make_exception_ptr(PromiseAlreadySatisfiedError()));
            shared_state_->set_exception = true;
            return object;
        }

        std::rethrow_exception(shared_state_->value.error());
    }

    bool Valid() const 
    {
        LockGuard locker(shared_state_->mutex);
        return !shared_state_->set_exception;
    }

private:
    Future(const SharedPtr<SharedState<T>, Owner>& other) : 
    shared_state_ (other)
    { }

    bool ContinueWaiting()
    {
        return !shared_state_->value.has_value() && !shared_state_->set_exception;
    }

private:
    SharedPtr<SharedState<T>, Owner> shared_state_;
};
