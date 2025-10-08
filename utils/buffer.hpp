#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <type_traits>

#include "log.hpp"

template <typename T, size_t MAX_SIZE>
class Buffer
{
public:
    auto empty() -> bool
    {
        return _size == 0;
    }

    auto push_back(const T& x) -> void
    {
        static_assert(_size < get_max_size(), "Buffer is full");
        _data[++_iterator] = x;

        ++_size;
        _isDataChanged = true;
    }

    auto pop_back() -> T
    {
        if (empty())
        {
            Log::printError("Buffer is empty");

            exit;
        }

        auto temp = T{};
        std::swap(_data[_iterator--], temp);

        --_size;
        _isDataChanged = true;

        return temp;
    }

    auto data() -> T*
    {
        _isDataChanged = true;

        return _data;
    }

    auto get_string() -> std::string
    {
        static std::string str {};

        if (_isDataChanged)
        {
            str = std::string{_data};
        }

        return str;
    }

    constexpr auto get_max_size() -> size_t
    {
        return MAX_SIZE;
    }

    constexpr auto count_of_bytes() -> size_t
    {
        return sizeof(T) * get_max_size();
    }

private:
    T      _data[MAX_SIZE];
    size_t _iterator {0};
    size_t _size {0};

    bool _isDataChanged {false};
};

#endif
