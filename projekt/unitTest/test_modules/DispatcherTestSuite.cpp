#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dispatcher.hpp"
#include "ErrorHandlerMock.hpp"
#include "UnixWrapperMock.hpp"
#include "ServerSendFileRequestHandlerMock.hpp"
#include "ServerSendFileListRequestHandlerMock.hpp"
#include <string>

using ::testing::StrictMock;
using ::testing::_;

class DispatcherTestSuite : public testing::Test
{
public:
    DispatcherTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_serverSendFileRequestHandlerMock(std::make_shared<StrictMock<ServerSendFileRequestHandlerMock>>()),
          m_serverSendFileListRequestHandlerMock(std::make_shared<StrictMock<ServerSendFileListRequestHandlerMock>>()),
          m_sut(m_unixWrapperMock, m_serverSendFileRequestHandlerMock, m_serverSendFileListRequestHandlerMock)
    {

    }

    void fillMessageStructureForServerSendFileReq(Message& p_msg, const std::string& p_fileName);
    void checkCapturedStdOutput(const std::string& p_expectedText);

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    std::shared_ptr<StrictMock<ServerSendFileRequestHandlerMock>> m_serverSendFileRequestHandlerMock;
    std::shared_ptr<StrictMock<ServerSendFileListRequestHandlerMock>> m_serverSendFileListRequestHandlerMock;
    Dispatcher m_sut;
};

void DispatcherTestSuite::fillMessageStructureForServerSendFileReq(Message& p_msg,
                                                                   const std::string& p_fileName)
{
    p_msg.msgId = SERVER_SEND_FILE_REQ;
    strcpy(p_msg.payload, p_fileName.c_str());
    p_msg.bytesInPayload = strlen(p_fileName.c_str());
    p_msg.numOfMsgInFileTransfer = 1;
}

void DispatcherTestSuite::checkCapturedStdOutput(const std::string& p_expectedText)
{
    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(p_expectedText, l_actualValue);
}

TEST_F(DispatcherTestSuite, testIfMessageWillBeSentDuringDispatchingEventWithCaseOne)
{
    const int l_someSocket = 5;
    Message l_msg;
    l_msg.msgId = SERVER_TEST_FIRST_REQ;
    strcpy(l_msg.payload, "Sample msg");

    Message l_sendline;
    l_sendline.msgId = SERVER_TEST_FIRST_RESP;
    strcpy(l_sendline.payload, "Odpowiedz");

    std::string l_expectedText = "PID: 0 | Case SERVER_TEST_FIRST_REQ: received message - Sample msg\n";
    testing::internal::CaptureStdout();
    EXPECT_CALL(*m_unixWrapperMock, getPid());
    EXPECT_CALL(*m_unixWrapperMock, send(l_someSocket, _, sizeof(l_sendline), 0));

    m_sut.dispatch(l_someSocket, l_msg);
    checkCapturedStdOutput(l_expectedText);
}

TEST_F(DispatcherTestSuite, testIfMessageWillNotBeSentDuringDispatchingEventWithCaseTwo)
{
    const int l_someSocket = 5;
    Message l_msg;
    l_msg.msgId = SERVER_TEST_SECOND_REQ;
    strcpy(l_msg.payload, "Sample msg");

    std::string l_expectedText = "PID: 0 | Case SERVER_TEST_SECOND_REQ: received message - Sample msg\n";
    testing::internal::CaptureStdout();
    EXPECT_CALL(*m_unixWrapperMock, getPid());

    m_sut.dispatch(l_someSocket, l_msg);
    checkCapturedStdOutput(l_expectedText);
}

TEST_F(DispatcherTestSuite, testIfServerSendFileRequestHandlerWillBeCalledDuringDispatchingEventServerSendFileReq)
{
    const int l_someSocket = 5;
    std::string l_fileName = "Sample.txt";
    Message l_msg = {};

    fillMessageStructureForServerSendFileReq(l_msg, l_fileName);
    std::string l_expectedText = "PID: 0 | Case SERVER_SEND_FILE_REQ: received message - Sample.txt\n";
    testing::internal::CaptureStdout();

    EXPECT_CALL(*m_unixWrapperMock, getPid());
    EXPECT_CALL(*m_serverSendFileRequestHandlerMock, handle(l_someSocket, l_msg));

    m_sut.dispatch(l_someSocket, l_msg);
    checkCapturedStdOutput(l_expectedText);
}

TEST_F(DispatcherTestSuite, testIfServerSendFileListRequestHandlerWillBeCalledDuringDispatchingEventServerSendFileListReq)
{
    const int l_someSocket = 5;
    Message l_msg = {};
    l_msg.msgId = SERVER_SEND_FILE_LIST_REQ;
    strcpy(l_msg.payload, "File list request.");

    std::string l_expectedText = "PID: 0 | Case SERVER_SEND_FILE_LIST_REQ: received message - File list request.\n";
    testing::internal::CaptureStdout();

    EXPECT_CALL(*m_unixWrapperMock, getPid());
    EXPECT_CALL(*m_serverSendFileListRequestHandlerMock, handle(l_someSocket, l_msg));

    m_sut.dispatch(l_someSocket, l_msg);
    checkCapturedStdOutput(l_expectedText);
}

TEST_F(DispatcherTestSuite, testIfMessageWillNotBeSentDuringDispatchingEventWithUnknownCase)
{
    const int l_someSocket = 5;
    Message l_msg;
    l_msg.msgId = CLIENT_WELCOME_MSG_IND;
    strcpy(l_msg.payload, "Sample msg");

    std::string l_expectedText = "PID: 0 | Unknown message identyfier\n";
    testing::internal::CaptureStdout();
    EXPECT_CALL(*m_unixWrapperMock, getPid());

    m_sut.dispatch(l_someSocket, l_msg);
    checkCapturedStdOutput(l_expectedText);
}
