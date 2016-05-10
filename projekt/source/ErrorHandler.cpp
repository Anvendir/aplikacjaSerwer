#include "ErrorHandler.hpp"

#include <iostream>
#include <cstdio>
#include <cstring>

ErrorHandler::ErrorHandler()
{

}

void ErrorHandler::handleSoftError(const std::string p_errorMessage) const
{
    std::cerr << "Warning: " << p_errorMessage
              << " - " << strerror(errno)
              << std::endl;
}

void ErrorHandler::handleHardError(const std::string p_errorMessage) const
{
    std::cerr << "Error: " << p_errorMessage
              << " - " << strerror(errno)
              << ", application is going to be terminated."
              << std::endl;

    exit(-1);
}
