#include "ErrorHandler.hpp"

#include <iostream>
#include <cstdio>
#include <cstring>

void ErrorHandler::handleSoftError(std::string p_errorMessage)
{
    std::cerr << "Warning: " << p_errorMessage
              << " - " << strerror(errno)
              << std::endl;
}

void ErrorHandler::handleHardError(std::string p_errorMessage)
{
    std::cerr << "Error: " << p_errorMessage 
              << " - " << strerror(errno) 
              << ", application is going to be terminated."
              << std::endl;

    exit(-1);
}
