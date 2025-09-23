#include <sys/socket.h>
#include <algorithm>
#include <cmath>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <numeric>
#include <stdexcept>

#include "functions.hpp"

void functions::runFirstThread(
    std::shared_ptr<std::mutex>              sharedMtx,
    std::shared_ptr<std::condition_variable> sharedCond,
    std::shared_ptr<Buffer>                  sharedBuff,
    bool&                                    secondOut)
{
    while (true)
    {
        std::unique_lock<std::mutex> lg{ *sharedMtx };

        (*sharedCond).wait(lg, [&]() { return secondOut; });

        std::string numStr = "";

        numStr = readFromInput();

        if (numStr.empty())
        {
            continue;
        }

        handleNumString(numStr);

        (*sharedBuff).push(numStr);

        secondOut = false;

        (*sharedCond).notify_one();
    }
}

void functions::runSecondThread(
    std::shared_ptr<std::mutex>               sharedMtx,
    std::shared_ptr<std::condition_variable>  sharedCond,
    std::shared_ptr<Buffer>                   sharedBuff,
    bool &                                      secondOut,
    int  &                                      sock,
    int  &                                      listener)
{
    bool secondConnected = false;

    auto plusLambda = [] (const int& _lx, const int& _rx) -> int
    {
        return _lx + (isdigit(_rx) ? (_rx - '0') : 0);
    };

    while (true)
    {
        std::unique_lock<std::mutex> lg{ *sharedMtx };

        (*sharedCond).wait(lg,[&](){ return !(*sharedBuff).empty(); });

        std::string dataStr = (*sharedBuff).pop();
        std::cout << "result line: " << dataStr << '\n';

        int sum = std::accumulate(dataStr.begin(), dataStr.end(), 0, plusLambda);

        int N = 1;

        {
            int nMax = 3;
            int tempSum = sum;

            for (int i = 1; i < nMax; i++)
            {
                int raisedTen = std::pow(10, i);

                if (tempSum / raisedTen == 0)
                {
                    break;
                }

                N++;
            }
        }

        int tempSum = sum;

        char data[N]{ 0 };

        for (int i = 0; i < N; i++)
        {
            int raisedTen = std::pow(10, N - i - 1);
            data[i] = tempSum / raisedTen + '0';
            tempSum = tempSum % raisedTen;
        }

        if (send(sock, data, N, MSG_NOSIGNAL) == -1)
        {
            sock = accept(listener, nullptr, nullptr);

            if (sock >= 0)
            {
                std::cout << "connected to program 2\n";
                send(sock, data, N, MSG_NOSIGNAL);
            }
        }

        std::cout << '\n';

        secondOut = true;
        (*sharedCond).notify_one();
    }
}

std::string functions::readFromInput()
{
    std::string numStr;

    try
    {
        std::cout << "enter line: ";
        std::getline(std::cin, numStr);

        if (numStr.length() > 64)
        {
            throw std::invalid_argument("error: length > 64");
        }
        if (!std::all_of(numStr.begin(), numStr.end(), isdigit))
        {
            throw std::invalid_argument("error: not digits only");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }

    return numStr;
}

void functions::handleNumString(std::string& numStr)
{
    std::sort(numStr.begin(), numStr.end(), std::greater< char >());

    int pos{};

    while (pos < numStr.length())
    {
        if (numStr.at(pos) % 2 == 0)
        {
            numStr.replace(pos, 1, "KB");
            pos += 2;
        }
        else
        {
            pos++;
        }
    }
}
