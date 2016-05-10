#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "UnixWrappers.hpp"
#include "ErrorHandlerMock.hpp"
#include "MessageConverterMock.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <memory>

using ::testing::StrictMock;
using ::testing::Return;

class UnixWrappersTestSuite : public ::testing::Test
{
public:
    UnixWrappersTestSuite() :
         m_errorHandler(std::make_shared<StrictMock<ErrorHandlerMock>>()),
         m_messageConverterMock(std::make_shared<StrictMock<MessageConverterMock>>()),
         m_sut(m_errorHandler, m_messageConverterMock)
    {

    }

    std::shared_ptr<StrictMock<ErrorHandlerMock>> m_errorHandler;
    std::shared_ptr<StrictMock<MessageConverterMock>> m_messageConverterMock;
    UnixWrappers m_sut;
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

    Message l_message;
    strcpy(l_message.payload, "Hello world");

    RawMessage l_rawMessage = {};
    EXPECT_CALL(*m_messageConverterMock,
                convertMessageToRawMessage(l_message)).WillOnce(Return(l_rawMessage));

    m_sut.send(l_sockFd, &l_message, sizeof(RawMessage));
}

TEST_F(UnixWrappersTestSuite, testIfSendFunctionWillHandleHardErrorWithIncorrectCall)
{
    int l_fakeSockFd = 1;

    EXPECT_CALL(*m_errorHandler, handleHardError("send error"));
    Message l_message;
    strcpy(l_message.payload, "Hello world");

    RawMessage l_rawMessage = {};
    EXPECT_CALL(*m_messageConverterMock,
                convertMessageToRawMessage(l_message)).WillOnce(Return(l_rawMessage));

    m_sut.send(l_fakeSockFd, &l_message, sizeof(RawMessage));
}

TEST_F(UnixWrappersTestSuite, testIfRecvFunctionWillHandlehardErrorWithIncorrectCall)
{
    int l_fakeSockFd = 1;
    Message l_receivedMessage;

    EXPECT_CALL(*m_errorHandler, handleHardError("recv error"));
    m_sut.recv(l_fakeSockFd, &l_receivedMessage, sizeof(Message));
}

TEST_F(UnixWrappersTestSuite, testIfCloseFunctionWillHandleNoErrorWithProperCall)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    m_sut.close(l_sockFd);
}

TEST_F(UnixWrappersTestSuite, testIfCloseFunctionWillHandlehardErrorWithIncorrectCall)
{
    int l_fakeSockFd = -41;

    EXPECT_CALL(*m_errorHandler, handleHardError("close error"));
    m_sut.close(l_fakeSockFd);
}

