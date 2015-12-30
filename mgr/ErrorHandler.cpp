#include "ErrorHandler.hpp"

#include <iostream>
#include <cstdio>

void ErrorHandler::handleSoftError(std::string p_errorMessage)
{
    std::cerr << "Warning: " << p_errorMessage << std::endl;
}

void ErrorHandler::handleHardError(std::string p_errorMessage)
{
    std::cerr << "Error: " << p_errorMessage 
              << ", application is going to be terminated."
              << std::endl;

    exit(-1);
}
