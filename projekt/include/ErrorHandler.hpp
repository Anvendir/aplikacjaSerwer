#include "IErrorHandler.hpp"
#include <string>

#pragma once

class ErrorHandler : public IErrorHandler
{
public:
    ErrorHandler();
    void handleSoftError(std::string p_errorMessage) const override;
    void handleHardError(std::string p_errorMessage) const override;

private:
};
