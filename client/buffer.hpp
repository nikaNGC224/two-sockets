#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <queue>
#include <string>

class Buffer
{
private:
    std::string str_;
public:
    bool empty();
    void push(const std::string& x);
    std::string pop();
};

#endif
