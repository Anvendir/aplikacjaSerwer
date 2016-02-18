#include <iostream>
#include "Dispatcher.hpp"
#include "ErrorHandler.hpp"
#include "Server.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    //ErrorHandler m;
    //m.handleHardError("O kurwa!");
    //Dispatcher d;
    //d.dispatch();
    Server s;
    s.start();

    return 0;
}
