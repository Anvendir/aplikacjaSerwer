#include <iostream>
#include "Dispatcher.hpp"
#include "ErrorHandler.hpp"
#include "Server.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Server l_server;
    l_server.start();

    return 0;
}
