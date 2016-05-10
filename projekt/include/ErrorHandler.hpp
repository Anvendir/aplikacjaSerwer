#include "IErrorHandler.hpp"
#include <string>

#pragma once

class ErrorHandler : public IErrorHandler
{
public:
    ErrorHandler();
    void handleSoftError(const std::string p_errorMessage) const override;
    void handleHardError(const std::string p_errorMessage) const override;

private:
};
