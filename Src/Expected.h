#pragma once

template <class ErrorT>
class Unexpected;

template <class ValueT, class ErrorT>
class Expected
{
    Expected(const Expected& other) = default;
    Expected(Expected&& other) = default;

    Expected(Unexpected<ErrorT> unexpected);
    Expected(ValueT&& value);

    bool HasValue();

    ValueT& Value();
    const ValueT& Value() const;

    ErrorT& Error();
    const ErrorT& Error() const;

    ValueT* operator->();
    const ValueT* operator->() const;

    ValueT& operator*();
    const ValueT& operator*() const;

    bool operator==(const Expected& other);

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
