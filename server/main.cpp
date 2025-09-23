#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <thread>

#include "functions.hpp"

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char data[3];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener < 0)
    {
        std::cerr << "error: socket\n";
        return 1;
    }

    fcntl(listener, F_SETFL, O_NONBLOCK);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5421);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int yes = 1;

    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cerr << "error: setsockopt\n";
        return 2;
    }

    if (bind(listener, (struct sockaddr *)& addr, sizeof(addr)) < 0)
    {
        std::cerr << "error: bind\n";
        return 2;
    }

    listen(listener, 1);
    sock = accept(listener, nullptr, nullptr);

    if (sock >= 0)
    {
        std::cout << "connected to program 2\n";
    }

    std::mutex mtx;
    std::condition_variable cond;
    Buffer buffer;
    bool secondOut = true;

    std::thread firstThread(
        functions::runFirstThread,
        std::make_shared<std::mutex>(mtx),
        std::make_shared<std::condition_variable>(cond),
        std::make_shared<Buffer>(buffer),
        std::ref(secondOut)
    );

    std::thread secondThread(
        functions::runSecondThread,
        std::make_shared<std::mutex>(mtx),
        std::make_shared<std::condition_variable>(cond),
        std::make_shared<Buffer>(buffer),
        std::ref(secondOut),
        std::ref(sock),
        std::ref(listener)
    );

    firstThread.join();
    secondThread.join();
}
