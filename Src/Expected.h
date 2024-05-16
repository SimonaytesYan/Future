#pragma once

template <class ErrorT>
class Unexpected;

template <class ValueT, class ErrorT>
class Expected
{
    Expected(const Expected& other) = default;
    Expected(Expected&& other) = default;

    Expected(Unexpected<ErrorT>&& unexpected) :
    has_value (false),
    error     (unexpected.Error())
    { }

    Expected(ValueT&& value) :
    has_value (true),
    value (value)
    { }

    bool HasValue()
    { return has_value; }
    
    ValueT& Value()
    { return value; }
    const ValueT& Value() const
    { return value; }

    ErrorT& Error()
    { return error; }
    const ErrorT& Error() const
    { return error; }

    ValueT* operator->()
    { return &value; }
    const ValueT* operator->() const
    { return &value; }

    ValueT& operator*()
    { return value; }
    const ValueT& operator*() const
    { return value; }

    bool operator==(const Expected& other)
    {
        if (has_value != other.has_value)
            return false;
        
        if (has_value)
            return value == other.value;
        return error == other.error;
    }

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
    Unexpected(ErrorT&& error) :
    error (error)
    { }

    ErrorT& Error()
    { return error; }

    bool operator==(const Unexpected& other)
    { return error == other.error; }

private:
    ErrorT error;
};
