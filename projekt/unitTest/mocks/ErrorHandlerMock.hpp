#include "gmock/gmock.h"
#include <iostream>

class ErrorHandlerMock : public IErrorHandler
{
public:
    MOCK_CONST_METHOD1(handleSoftError, void(std::string));
    MOCK_CONST_METHOD1(handleHardError, void(std::string));
};
