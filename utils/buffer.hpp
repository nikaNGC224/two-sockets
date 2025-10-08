#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <type_traits>

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

        ++_iterator;

        _data[_iterator] = x;

        ++_size;
    }

    auto pop_back() -> T
    {
        if (empty())
        {
            printf("\n");
            printf("Buffer is empty");

            exit;
        }

        auto temp = T{};

        std::swap(_data[_iterator], temp);

        --_iterator;
        --_size;

        return temp;
    }

    auto data() -> T*
    {
        return _data;
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

};

#endif
