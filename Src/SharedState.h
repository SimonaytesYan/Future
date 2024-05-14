#pragma once

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
  twist::ed::std::mutex                mutex;
  twist::ed::std::condition_variable   continue_waiting;
};
