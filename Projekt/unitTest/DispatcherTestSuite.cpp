#include "gtest/gtest.h"
#include "Dispatcher.hpp"
#include <string>

class DispatcherTestSuite : public testing::Test
{
public:
    DispatcherTestSuite()
        : m_sut()
    {

    }

    Dispatcher m_sut;
};

TEST_F(DispatcherTestSuite, testIfProperMessageIsPrintedAfterCall_dispatch)
{
    std::string l_expectedText = "Dispatcher started... \n";

    testing::internal::CaptureStdout();
    m_sut.dispatch();
    std::string l_actualValue = testing::internal::GetCapturedStdout();

    EXPECT_EQ(l_expectedText, l_actualValue);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
