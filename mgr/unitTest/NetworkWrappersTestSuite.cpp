#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "NetworkWrappers.hpp"
#include "ErrorHandlerMock.hpp"

#include <sys/socket.h>

using ::testing::StrictMock;

class NetworkWrappersTestSuite : public ::testing::Test
{
public:
    NetworkWrappersTestSuite() :
         m_errorHandler(), m_sut(m_errorHandler)
    {

    }

    NetworkWrappers m_sut;
    StrictMock<ErrorHandlerMock> m_errorHandler;
};

TEST_F(NetworkWrappersTestSuite, testIfNonNegativeNumberWillBeReturnedAfterCorrectCall_socket)
{
    int l_result = m_sut.socket(AF_INET, SOCK_STREAM, 0);
    EXPECT_GE(l_result , 0);   
}

TEST_F(NetworkWrappersTestSuite, testIfNegativeNumberWillBeReturnedAfterIncorrectCall_socket)
{
    EXPECT_CALL(m_errorHandler, handleHardError("socket error"));
    int l_result = m_sut.socket(999, SOCK_STREAM, 0);
    EXPECT_EQ(l_result, -1); 
}

int main(int argc, char** argv)
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
