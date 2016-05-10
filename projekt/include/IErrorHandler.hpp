#include <string>

#pragma once

class IErrorHandler
{
public:
    virtual void handleSoftError(const std::string p_errorMessage) const = 0;
    virtual void handleHardError(const std::string p_errorMessage) const = 0;
};
