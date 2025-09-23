#include "buffer.hpp"

bool Buffer::empty()
{
    return str_.empty();
}

void Buffer::push(const std::string& x)
{
    if (str_.empty())
    {
        str_ = x;
    }
}

std::string Buffer::pop()
{
    return std::move(str_);
}
