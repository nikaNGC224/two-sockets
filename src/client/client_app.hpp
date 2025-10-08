/* Class of client application */

#ifndef CLIENT_APP_HPP
#define CLIENT_APP_HPP

#include <chrono>
#include <netinet/in.h>
#include <fcntl.h>

#include "../../utils/log.hpp"

class ClientApp
{
public:
    ClientApp()
    {
        initSocket();
    }

    auto run() -> int
    {
        connectToServer();
        sendDataToClient();

        return 0;
    }

    ~ClientApp()
    {
        ::shutdown(_socket, 0);
    }

private:
    auto initSocket() -> int
    {
        _socket = ::socket(AF_INET, SOCK_STREAM, 0);

        if (_socket < 0)
        {
            Log::printError("Init socket");

            return 1;
        }

        _serverAddress.sin_family = AF_INET;
        _serverAddress.sin_port = ::htons(5421);
        _serverAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);

        return 0;
    }

    auto connectToServer() -> int
    {
        static constexpr std::chrono::seconds connectPeriodSec {1};

        int res {};
        auto lastTimestamp = std::chrono::steady_clock::now();
        std::chrono::_V2::steady_clock::time_point currTimestamp {};

        while (true)
        {
            currTimestamp = std::chrono::steady_clock::now();

            if ((currTimestamp - lastTimestamp) >= connectPeriodSec)
            {
                lastTimestamp = currTimestamp;

                res = ::connect(_socket, (struct sockaddr*)&_serverAddress,
                                sizeof(_serverAddress));

                if (res == 0)
                {
                    Log::printInfo("Client has connected to server");

                    return 0;
                }
                else
                {
                    Log::printInfo("Connecting to server...");
                }
            }
        }
    }

    auto sendDataToClient() -> void
    {
        std::string test {"Hello!"};

        Log::printInfo("Send message \"" + test + "\" to server");

        ::send(_socket, test.c_str(), 6, 0);
    }

    int         _socket {};
    sockaddr_in _serverAddress {};
};

#endif
