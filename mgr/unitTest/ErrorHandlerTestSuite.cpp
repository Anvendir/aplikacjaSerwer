#include "ErrorHandler.hpp"
#include "gtest/gtest.h"
#include <string>

class ErrorHandlerTestSuite : public testing::Test
{
public:
    ErrorHandlerTestSuite()
        : m_sut()
    {

    }
    
    ErrorHandler m_sut;
};

TEST_F(ErrorHandlerTestSuite, testIfProperMessageIsPrintedAfterCall_handleSoftError)
{
    std::string l_errorDescription = "Example error message";
    std::string l_expectedErrorMessage = "Warning: " + l_errorDescription + "\n";

    testing::internal::CaptureStderr();
    m_sut.handleSoftError(l_errorDescription);
    std::string l_actualValue = testing::internal::GetCapturedStderr();

    EXPECT_EQ(l_expectedErrorMessage, l_actualValue);
}

TEST_F(ErrorHandlerTestSuite, testIfProperMessageIsPrintedAfterCall_handleHardError)
{
    std::string l_errorDescription = "Example error message";
    std::string l_expectedErrorMessage = "Error: " + l_errorDescription + ", application is going to be terminated.\n";
    
    EXPECT_DEATH(m_sut.handleHardError(l_errorDescription), l_expectedErrorMessage);
}

int main(int argc, char **argv)
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
