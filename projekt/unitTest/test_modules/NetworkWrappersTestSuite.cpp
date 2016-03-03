#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NetworkWrappers.hpp"
#include "ErrorHandlerMock.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

using ::testing::StrictMock;

class NetworkWrappersTestSuite : public ::testing::Test
{
public:
    NetworkWrappersTestSuite()
        : m_errorHandler(std::make_shared<StrictMock<ErrorHandlerMock>>()),
          m_sut(m_errorHandler)

    {

    }

    std::shared_ptr<StrictMock<ErrorHandlerMock>> m_errorHandler;
    NetworkWrappers m_sut;
};

TEST_F(NetworkWrappersTestSuite, testIfNonNegativeNumberWillBeReturnedAfterCorrectCall_socket)
{
    int l_result = m_sut.socket(AF_INET, SOCK_STREAM, 0);
    EXPECT_GE(l_result , 0);
}

TEST_F(NetworkWrappersTestSuite, testIfNegativeNumberWillBeReturnedAfterIncorrectCall_socket)
{
    EXPECT_CALL(*m_errorHandler, handleHardError("socket error"));
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

    EXPECT_CALL(*m_errorHandler, handleHardError("connect error"));
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

    EXPECT_CALL(*m_errorHandler, handleHardError("bind error"));
    m_sut.bind(1, &l_genericSockAddr, sizeof(l_genericSockAddr));
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterIncorrectCall_listen)
{
    int l_fakeSocketFd = 10;

    EXPECT_CALL(*m_errorHandler, handleHardError("listen error"));
    m_sut.listen(l_fakeSocketFd, -1);
}

TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_listen)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
    m_sut.listen(l_sockFd, 2);
}

/*TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_accept)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);

    SockAddrIn l_clientAddrFromServerSite;
    socklen_t l_len = sizeof(l_clientAddrFromServerSite);

    SockAddrIn l_serverAddr;
    memset(&l_serverAddr, 0, sizeof(l_serverAddr));
    l_serverAddr.sin_family = AF_INET;
    l_serverAddr.sin_port = ::htons(9999);
    ::inet_pton(AF_INET, "127.0.0.1", &l_serverAddr.sin_addr);

    ::bind(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_serverAddr), sizeof(l_serverAddr));
    ::listen(l_sockFd, 1);

    int l_sockFdClient = ::socket(AF_INET, SOCK_STREAM, 0);
    SockAddrIn l_serverAddrFromClientSite;
    memset(&l_serverAddrFromClientSite, 0, sizeof(l_serverAddrFromClientSite));
    l_serverAddrFromClientSite.sin_family = AF_INET;
    l_serverAddrFromClientSite.sin_port = ::htons(9999);
    ::inet_pton(AF_INET, "127.0.0.1", &l_serverAddrFromClientSite.sin_addr);

    ::connect(l_sockFdClient,
              reinterpret_cast<GenericSockAddr*>(&l_serverAddrFromClientSite),
              sizeof(l_serverAddrFromClientSite));

    m_sut.accept(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_clientAddrFromServerSite), &l_len);

    //There is a problem with testing of that function caused by blocked operation of accept and neccesity of
    //sending connect from another proces to test - no testable by unittest Rafal Kobak 15.02.2015
}*/

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterIncorrectCall_accept)
{
    int l_sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
    SockAddrIn l_clientAddrFromServerSite;
    socklen_t l_len = sizeof(l_clientAddrFromServerSite);

    EXPECT_CALL(*m_errorHandler, handleHardError("accept error"));
    m_sut.accept(l_sockFd, reinterpret_cast<GenericSockAddr*>(&l_clientAddrFromServerSite), &l_len);
}

TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_pton)
{
    SockAddrIn l_addr;
    unsigned long int l_expectedOutput = 33532096;

    const char* l_addresInPresFormat = "192.168.255.1";

    m_sut.pton(AF_INET, l_addresInPresFormat, &l_addr.sin_addr);
    ASSERT_EQ(l_expectedOutput, l_addr.sin_addr.s_addr);
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledWhenZeroOrNegativeIsReturned_pton)
{
    SockAddrIn l_addr;
    unsigned long int l_expectedOutput = 0;

    const char* l_addresInPresFormat = "192.168.255.@";
    EXPECT_CALL(*m_errorHandler, handleHardError("inet_pton error for 192.168.255.@"));

    m_sut.pton(AF_INET, l_addresInPresFormat, &l_addr.sin_addr);
}

TEST_F(NetworkWrappersTestSuite, testIfNoHandleErrorWillBeCalledAfterCorrectCall_ntop)
{
    unsigned long int l_addrInNetworkFormat = 33532096;
    SockAddrIn l_addr;
    l_addr.sin_addr.s_addr = l_addrInNetworkFormat;

    char l_output[INET_ADDRSTRLEN];
    const char* l_expectedOutput = "192.168.255.1";

    m_sut.ntop(AF_INET, &(l_addr.sin_addr), l_output, INET_ADDRSTRLEN);
    ASSERT_STREQ(l_expectedOutput, l_output);
}

TEST_F(NetworkWrappersTestSuite, testIfFunctionCrashAfterCallFunctionWithNullArgument_ntop)
{
    //in regular situation m_erroHandle will be called and exit with status 0
    unsigned long int l_addrInNetworkFormat = 33532096;
    SockAddrIn l_addr;
    l_addr.sin_addr.s_addr = l_addrInNetworkFormat;

    EXPECT_DEATH(m_sut.ntop(AF_INET, &(l_addr.sin_addr), NULL, INET_ADDRSTRLEN), "");
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterCallFunctionWithFakeProtocolFamily_ntop)
{
    unsigned long int l_addrInNetworkFormat = 33532096;
    SockAddrIn l_addr;
    l_addr.sin_addr.s_addr = l_addrInNetworkFormat;

    char l_output[INET_ADDRSTRLEN];
    const char* l_expectedOutput = "192.168.255.1";
    int l_fakeProtocolFamily = 12;

    EXPECT_CALL(*m_errorHandler, handleHardError("inet_ntop error"));
    m_sut.ntop(l_fakeProtocolFamily, &(l_addr.sin_addr), l_output, INET_ADDRSTRLEN);
}

TEST_F(NetworkWrappersTestSuite, testIfHandleHardErrorWillBeCalledAfterCallFunctionWithAddressFamilyDifferentThanAfInet_sockNtop)
{
    unsigned long int l_addrInNetworkFormat = 33532096;
    SockAddrIn l_addr;
    l_addr.sin_family = AF_INET6;
    l_addr.sin_addr.s_addr = l_addrInNetworkFormat;
    l_addr.sin_port = 21;

    EXPECT_CALL(*m_errorHandler, handleHardError("Unsupported socket address family!"));
    m_sut.sockNtop(reinterpret_cast<GenericSockAddr*>(&l_addr));
}

TEST_F(NetworkWrappersTestSuite, testIfFunctionWillReturnCorrectIpAddresAndIpInPresentationFormat_sockNtop)
{
    unsigned long int l_addrInNetworkFormat = 33532096;
    SockAddrIn l_addr;
    l_addr.sin_family = AF_INET;
    l_addr.sin_addr.s_addr = l_addrInNetworkFormat;
    l_addr.sin_port = ::htons(0b001'0110);

    const char* l_result = m_sut.sockNtop(reinterpret_cast<GenericSockAddr*>(&l_addr));
    EXPECT_STREQ("192.168.255.1:22", l_result);
}

