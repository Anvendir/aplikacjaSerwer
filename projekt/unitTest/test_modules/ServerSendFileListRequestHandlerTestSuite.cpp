#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerSendFileListRequestHandler.hpp"
#include "UnixWrapperMock.hpp"

using ::testing::StrictMock;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::StartsWith;

class ServerSendFileListRequestHandlerTestSuite : public testing::Test
{
public:
    ServerSendFileListRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    ServerSendFileListRequestHandler m_sut;
};

TEST_F(ServerSendFileListRequestHandlerTestSuite, testHandleMethodInSuccessfullCase)
{
    Message l_msg = {};
    int l_clientSocket = 5;

    EXPECT_CALL(*m_unixWrapperMock, executeCommand(StrEq("git rev-parse --show-toplevel")))
        .WillOnce(Return("/root\n"));
    EXPECT_CALL(*m_unixWrapperMock, executeCommand(StrEq("ls /root/projekt/moduleTest/plikiPrzykladowe/")))
        .WillOnce(Return("someFile.txt"));
    EXPECT_CALL(*m_unixWrapperMock, send(l_clientSocket,
                                         AllOf(Field(&Message::msgId, SERVER_SEND_FILE_LIST_RESP),
                                               Field(&Message::numOfMsgInFileTransfer, 0),
                                               Field(&Message::bytesInPayload, std::string("someFile.txt").size()),
                                               Field(&Message::payload, StartsWith("someFile.txt"))),
                                         sizeof(RawMessage),
                                         0));
    m_sut.handle(l_clientSocket, l_msg);
}

TEST_F(ServerSendFileListRequestHandlerTestSuite, testHandleMethodInCaseWhenSearchingRepoRootFails)
{
    Message l_msg = {};
    int l_clientSocket = 5;

    EXPECT_CALL(*m_unixWrapperMock, executeCommand(StrEq("git rev-parse --show-toplevel")))
        .WillOnce(Return("ERROR"));
    EXPECT_CALL(*m_unixWrapperMock, send(l_clientSocket,
                                         AllOf(Field(&Message::msgId, SERVER_SEND_FILE_LIST_RESP),
                                               Field(&Message::numOfMsgInFileTransfer, 0),
                                               Field(&Message::bytesInPayload, 0)),
                                         sizeof(RawMessage),
                                         0));
    m_sut.handle(l_clientSocket, l_msg);
}

TEST_F(ServerSendFileListRequestHandlerTestSuite, testHandleMethodInCaseWhenExecutingLsCommandFails)
{
    Message l_msg = {};
    int l_clientSocket = 5;

    EXPECT_CALL(*m_unixWrapperMock, executeCommand(StrEq("git rev-parse --show-toplevel")))
        .WillOnce(Return("/root\n"));
    EXPECT_CALL(*m_unixWrapperMock, executeCommand(StrEq("ls /root/projekt/moduleTest/plikiPrzykladowe/")))
        .WillOnce(Return("ERROR"));
    EXPECT_CALL(*m_unixWrapperMock, send(l_clientSocket,
                                         AllOf(Field(&Message::msgId, SERVER_SEND_FILE_LIST_RESP),
                                               Field(&Message::numOfMsgInFileTransfer, 0),
                                               Field(&Message::bytesInPayload, 0)),
                                         sizeof(RawMessage),
                                         0));
    m_sut.handle(l_clientSocket, l_msg);
}

