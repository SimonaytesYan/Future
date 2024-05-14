#pragma once

#include <mutex>
#include <condition_variable>
#include <expected>

template <class T>
struct SharedState
{
  // Movable
  SharedState(SharedState<T>&& other) = default;
  SharedState& operator=(SharedState<T>&& other) = default;

  SharedState(std::expected<T, std::exception_ptr> other_value)
  {
    value = other_value;
  }

  std::expected<T, std::exception_ptr> value;
  std::mutex                mutex;
  std::condition_variable   continue_waiting;
};
