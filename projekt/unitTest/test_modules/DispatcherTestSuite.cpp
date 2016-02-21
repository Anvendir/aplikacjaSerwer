#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dispatcher.hpp"
#include "ErrorHandlerMock.hpp"
#include <string>

using ::testing::StrictMock;

class DispatcherTestSuite : public testing::Test
{
public:
    DispatcherTestSuite()
        : m_errorHandlerMock(std::make_shared<StrictMock<ErrorHandlerMock>>()),
          m_sut(m_errorHandlerMock)
    {

    }

    std::shared_ptr<StrictMock<ErrorHandlerMock>> m_errorHandlerMock;
    Dispatcher m_sut;
};

TEST_F(DispatcherTestSuite, emptyTest)
{

}

//Dopisac sensowny
/*TEST_F(DispatcherTestSuite, testIfProperMessageIsPrintedAfterCall_dispatch)
{
    std::string l_expectedText = "Dispatcher started... \n";

    testing::internal::CaptureStdout();
    m_sut.dispatch();
    std::string l_actualValue = testing::internal::GetCapturedStdout();

    EXPECT_EQ(l_expectedText, l_actualValue);
}*/
