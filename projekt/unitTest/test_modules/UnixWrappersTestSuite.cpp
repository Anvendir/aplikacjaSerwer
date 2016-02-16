#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "UnixWrappers.hpp"
#include "ErrorHandlerMock.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using ::testing::StrictMock;

class UnixWrappersTestSuite : public ::testing::Test
{
public:
    UnixWrappersTestSuite() :
         m_errorHandler(), m_sut(m_errorHandler)
    {

    }

    UnixWrappers m_sut;
    StrictMock<ErrorHandlerMock> m_errorHandler;
};

TEST_F(UnixWrappersTestSuite, testIfSendFunctionWillHandleNoErrorWithProperCall)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    SockAddrIn l_sockAddr;
    memset(&l_sockAddr, 0, sizeof(l_sockAddr));
    l_sockAddr.sin_family = AF_INET;
    l_sockAddr.sin_port = ::htons(22);
    ::inet_pton(AF_INET, "127.0.0.1", &l_sockAddr.sin_addr);
    ::connect(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_sockAddr), sizeof(l_sockAddr));

    const char* l_message = "Hello world";
    m_sut.send(l_sockFd, l_message, strlen(l_message));
}

TEST_F(UnixWrappersTestSuite, testIfSendFunctionWillHandleHardErrorWithIncorrectCall)
{
    int l_fakeSockFd = 1;

    EXPECT_CALL(m_errorHandler, handleHardError("send error"));
    const char* l_message = "Hello world";
    m_sut.send(l_fakeSockFd, l_message, strlen(l_message));
}

TEST_F(UnixWrappersTestSuite, testIfRecvFunctionWillHandlehardErrorWithIncorrectCall)
{
    int l_fakeSockFd = 1;
    char l_receivedMessage[10];

    EXPECT_CALL(m_errorHandler, handleHardError("recv error"));
    m_sut.recv(l_fakeSockFd, l_receivedMessage, sizeof(l_receivedMessage));
}

TEST_F(UnixWrappersTestSuite, testIfCloseFunctionWillHandleNoErrorWithProperCall)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    m_sut.close(l_sockFd);
}

TEST_F(UnixWrappersTestSuite, testIfCloseFunctionWillHandlehardErrorWithIncorrectCall)
{
    int l_fakeSockFd = -41;

    EXPECT_CALL(m_errorHandler, handleHardError("close error"));
    m_sut.close(l_fakeSockFd);
}

