#pragma once

template <class ValueT, class ErrorT>
class Expected
{
    bool HasValue();

    ValueT& Value();
    const ValueT& Value() const;
    ValueT&& Value();

    ErrorT& Error();
    const ErrorT& ErrorT() const;
    ErrorT&& ErrorT();

    ValueT* operator->();
    const ValueT* operator->() const;
    
    ValueT& operator*();
    const ValueT& operator*() const;

    bool operator==(const Unexpected& other);

private:
    bool has_value;
    union
    {
        ValueT value;
        ErrorT error;
    };
    
};

template <class ErrorT>
class Unexpected
{
    Unexpected(const Unexpected& other) = default; 
    Unexpected(Unexpected&& other)      = default;
    Unexpected(ErrorT&& error);

    ErrorT& Error();

    bool operator==(const Unexpected& other);

private:
    ErrorT error;
};
