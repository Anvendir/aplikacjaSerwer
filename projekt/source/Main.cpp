#include <iostream>
#include "Dispatcher.hpp"
#include "ErrorHandler.hpp"
#include "Server.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Server s;
    s.start();

    return 0;
}
