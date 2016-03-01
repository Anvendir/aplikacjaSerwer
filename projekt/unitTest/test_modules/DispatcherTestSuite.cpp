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
    const Message l_msg = {FIRST_CASE, "Sample msg"};
    Message l_sendline = {FIRST_CASE, "Odpowiedz"};

    std::string l_expectedText = "PID: 0 | Case 1: , otrzymana wiadomosc to - Sample msg\n";
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
    const Message l_msg = {SECOND_CASE, "Sample msg"};

    std::string l_expectedText = "PID: 0 | Case 2: , otrzymana wiadomosc to - Sample msg\n";
    testing::internal::CaptureStdout();
    EXPECT_CALL(*m_unixWrapperMock, getPid());

    m_sut.dispatch(l_someSocket, l_msg);

    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedText, l_actualValue);
}

TEST_F(DispatcherTestSuite, testIfMessageWillNotBeSentDuringDispatchingEventWithUnknownCase)
{
    const int l_someSocket = 5;
    const Message l_msg = {EMessageId(3), "Sample msg"};

    std::string l_expectedText = "PID: 0 | Nieznany identyfikator\n";
    testing::internal::CaptureStdout();
    EXPECT_CALL(*m_unixWrapperMock, getPid());

    m_sut.dispatch(l_someSocket, l_msg);

    std::string l_actualValue = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedText, l_actualValue);
}
