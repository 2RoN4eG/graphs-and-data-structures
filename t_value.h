#ifndef T_VALUE_H
#define T_VALUE_H

#include <functional>

template <typename t_value>
class t_value_holder
{
public:
    using t_value_type = t_value;

    t_value_holder(t_value value = std::numeric_limits<t_value>::max())
        : _value { value }
    {
    }

    t_value_holder(const t_value_holder<t_value>& other)
        : _value { other._value }
    {
    }

    t_value_holder<t_value>& operator=(const t_value_holder<t_value>& other) {
        new (this) t_value_holder<t_value>(other);
        return *this;
    }


    t_value_holder(t_value_holder<t_value>&& other)
        : _value { std::exchange(other._value, {}) }
    {
    }

    t_value_holder<t_value>& operator=(t_value_holder<t_value>&& other) {
        new (this) t_value_holder<t_value>(std::move(other));
        return *this;
    }


    const t_value operator()() const {
        return _value;
    }

protected:
    friend bool operator==(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
        return lhs._value == rhs._value;
    }

    friend bool operator<(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
        return lhs._value < rhs._value;
    }

    friend bool operator>(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
        return lhs._value > rhs._value;
    }

    t_value _value {};
};

template <typename t_value>
class t_value_generator
{

public:
    t_value_generator()
        : _value {}
    {
    }

    const t_value get_value_and_generate_next() {
        return _value ++;
    }

    const t_value get_value_and_generate_previous() {
        return _value --;
    }

protected:
    t_value _value {};
};

#endif // T_VALUE_H
