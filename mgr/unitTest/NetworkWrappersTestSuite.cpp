#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "NetworkWrappers.hpp"
#include "ErrorHandlerMock.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>

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

TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_connect)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    SockAddrIn l_sockAddr;
    memset(&l_sockAddr, 0, sizeof(l_sockAddr));
    l_sockAddr.sin_family = AF_INET;
    l_sockAddr.sin_port = ::htons(22);
    ::inet_pton(AF_INET, "127.0.0.1", &l_sockAddr.sin_addr);

    m_sut.connect(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_sockAddr), sizeof(l_sockAddr));
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterIncorrectCall_connect)
{
    GenericSockAddr l_genericSockAddr;

    EXPECT_CALL(m_errorHandler, handleHardError("connect error"));
    m_sut.connect(1, &l_genericSockAddr, sizeof(l_genericSockAddr));
}

TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_bind)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    SockAddrIn l_sockAddr;
    memset(&l_sockAddr, 0, sizeof(l_sockAddr));
    l_sockAddr.sin_family = AF_INET;
    l_sockAddr.sin_port = ::htons(9999);
    ::inet_pton(AF_INET, "127.0.0.1", &l_sockAddr.sin_addr);

    m_sut.bind(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_sockAddr), sizeof(l_sockAddr));
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterIncorrectCall_bind)
{
    GenericSockAddr l_genericSockAddr;

    EXPECT_CALL(m_errorHandler, handleHardError("bind error"));
    m_sut.bind(1, &l_genericSockAddr, sizeof(l_genericSockAddr));
}

int main(int argc, char** argv)
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
