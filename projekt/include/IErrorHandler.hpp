#include <string>

#pragma once

class IErrorHandler
{
public:
    virtual void handleSoftError(std::string p_errorMessage) const = 0;
    virtual void handleHardError(std::string p_errorMessage) const = 0;
};
