#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <condition_variable>
#include <iosfwd>
#include <mutex>

#include "buffer.hpp"

namespace functions
{
    std::string readFromInput();
    void handleNumString(std::string& str);

    void runFirstThread();

    void runSecondThread(
        int& sock,
        int& listener
    );
};

#endif
