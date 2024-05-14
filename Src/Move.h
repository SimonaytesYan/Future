#pragma once

template<class T>
T&& Move(T& object)
{ return (T&&)object; }
