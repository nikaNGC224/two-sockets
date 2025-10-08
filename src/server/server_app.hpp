/* Class of server application */

#ifndef SERVER_APP_HPP
#define SERVER_APP_HPP

// #include <chrono>
#include <netinet/in.h>
#include <fcntl.h>
#include <iostream>

#include "../../utils/buffer.hpp"

class ServerApp
{
public:
    ServerApp()
    {
        initSocket();
    }

    auto run() -> int
    {
        connectToClient();
        receiveDataFromClient();

        return 0;
    }

    ~ServerApp()
    {
        ::shutdown(_socket, 0);
    }

private:
    auto initSocket() -> int
    {
        _socket = ::socket(AF_INET, SOCK_STREAM, 0);

        if (_socket < 0)
        {
            printf("error: socket");
            printf("\n");

            return 1;
        }

        _serverAddress.sin_family = AF_INET;
        _serverAddress.sin_port = ::htons(5421);
        _serverAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);

        ::bind(_socket,
               (struct sockaddr*)&_serverAddress,
               sizeof(_serverAddress));

        return 0;
    }

    auto connectToClient() -> int
    {
        ::listen(_socket, 5);

        _clientSocket = ::accept(_socket, nullptr, nullptr);

        if (_clientSocket != -1)
        {
            printf("Client has connected to server");
            printf("\n");

            return 0;
        }
        else
        {
            printf("Connecting is failed");
            printf("\n");

            return 1;
        }
    }

    auto receiveDataFromClient() -> void
    {
        auto readBytes = ::recv(_clientSocket,
                                _buffer.data(),
                                _buffer.count_of_bytes(),
                                0);

        if (readBytes > 0)
        {
            printf("Received message: \"%s\"", _buffer.data());
            printf("\n");
        }
    }

    int                _socket {};
    int                _clientSocket {};
    sockaddr_in        _serverAddress {};
    Buffer<char, 1024> _buffer {};
};

#endif
