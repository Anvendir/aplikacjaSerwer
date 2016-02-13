#include "ErrorHandler.hpp"
#include "gtest/gtest.h"
#include <string>
#include <sys/socket.h>

class ErrorHandlerTestSuite : public testing::Test
{
public:
    ErrorHandlerTestSuite()
        : m_sut()
    {

    }

    ErrorHandler m_sut;
};

TEST_F(ErrorHandlerTestSuite, testIfProperMessageIsPrintedAfterCall_success_handleSoftError)
{
    std::string l_errorDescription = "Example error message";
    std::string l_expectedErrorMessage = "Warning: " + l_errorDescription + " - Success\n";

    testing::internal::CaptureStderr();
    m_sut.handleSoftError(l_errorDescription);
    std::string l_actualValue = testing::internal::GetCapturedStderr();

    EXPECT_EQ(l_expectedErrorMessage, l_actualValue);
}

TEST_F(ErrorHandlerTestSuite, testIfProperMessageIsPrintedAfterCall_exampleError_handleSoftError)
{
    std::string l_errorDescription = "Example error message";
    std::string l_expectedErrorMessage = "Warning: " +
                                         l_errorDescription +
                                         " - Address family not supported by protocol\n";

    socket(999, SOCK_STREAM, 0);

    testing::internal::CaptureStderr();
    m_sut.handleSoftError(l_errorDescription);
    std::string l_actualValue = testing::internal::GetCapturedStderr();

    EXPECT_EQ(l_expectedErrorMessage, l_actualValue);
}

TEST_F(ErrorHandlerTestSuite, testIfProperMessageIsPrintedAfterCall_success_handleHardError)
{
    std::string l_errorDescription = "Example error message";
    std::string l_expectedErrorMessage = "Error: " +
                                         l_errorDescription +
                                         " - Success, application is going to be terminated.\n";

    EXPECT_DEATH(m_sut.handleHardError(l_errorDescription), l_expectedErrorMessage);
}
