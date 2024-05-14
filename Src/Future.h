#pragma once

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
      // TODO implement
    }

    bool Valid() const 
    {
      // TODO implement
    }

 private:
    Future(const std::shared_ptr<SharedState<T>>& other) : 
    shared_state_ (other)
    { 
      printf("Future ctor\n");
    }

    bool ContinueWaiting()
    {
      // TODO implement
    }

 private:
  std::shared_ptr<SharedState<T>> shared_state_;
};
