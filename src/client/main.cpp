#include "client_app.hpp"

int main()
{
    auto clientApp = ClientApp();

    clientApp.run();

    // std::thread firstThread(functions::runFirstThread);

    /*
    std::thread secondThread(
        functions::runSecondThread,
        std::ref(sock),
        std::ref(listener)
    );
    */

    // firstThread.join();
    // secondThread.join();
}
