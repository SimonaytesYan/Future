#pragma once

template<class T>
T&& move(T& object)
{ return (T&&)object; }
