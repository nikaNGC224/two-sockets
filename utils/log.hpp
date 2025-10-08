#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

class Log
{
public:
    static auto printInfo(const std::string &msg) -> void
    {
        printf("%s", msg.c_str());
        printf("\n");
    }

    static auto printError(const std::string &msg) -> void
    {
        printf("error: ");
        printInfo(msg);
    }
};

#endif
