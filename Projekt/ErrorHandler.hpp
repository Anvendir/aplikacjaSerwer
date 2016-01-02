#include "IErrorHandler.hpp"
#include <string>

#pragma once

class ErrorHandler : public IErrorHandler
{
public:
    void handleSoftError(std::string p_errorMessage) override;
    void handleHardError(std::string p_errorMessage) override;
};
