#pragma once

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
    void SetValue(T value) 
    {
        // TODO implement
    }

    // One-shot
    void SetException(std::exception_ptr exception) 
    {
      // TODO implement
    }

    ~Promise() 
    {
        // TODO implement
    }

private:
    std::shared_ptr<SharedState<T>> shared_state_;
};
