#include <iostream>
#include "Dispatcher.hpp"
#include "ErrorHandler.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    ErrorHandler m;
    m.handleHardError("O kurwa!");
    Dispatcher d;
    d.dispatch();
    return 0;
}
