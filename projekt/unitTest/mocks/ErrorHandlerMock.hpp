#include "gmock/gmock.h"
#include "IErrorHandler.hpp"
#include <iostream>

class ErrorHandlerMock : public IErrorHandler
{
public:
    MOCK_CONST_METHOD1(handleSoftError, void(const std::string));
    MOCK_CONST_METHOD1(handleHardError, void(const std::string));
};
