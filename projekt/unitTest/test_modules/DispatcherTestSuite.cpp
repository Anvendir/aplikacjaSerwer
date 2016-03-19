#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dispatcher.hpp"
#include "ErrorHandlerMock.hpp"
#include "UnixWrapperMock.hpp"
#include <string>

using ::testing::StrictMock;
using ::testing::_;

class DispatcherTestSuite : public testing::Test
{
public:
    DispatcherTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    Dispatcher m_sut;
};

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

    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedText, l_actualValue);
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

    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedText, l_actualValue);
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

    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedText, l_actualValue);
}
