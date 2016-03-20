#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ServerSendFileRequestHandler.hpp"
#include "UnixWrapperMock.hpp"

#include <string>
#include <fstream>

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Field;

class ServerSendFileRequestHandlerTestTable : public ServerSendFileRequestHandler
{
public:
    ServerSendFileRequestHandlerTestTable(std::shared_ptr<IUnixWrappers> p_unixWrapper)
        : ServerSendFileRequestHandler(p_unixWrapper)
    {
    }

    void sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const
    {
        ServerSendFileRequestHandler::sendSeverSendFileResp(p_clientSocket, p_fileLength);
    }
    void sendClientSendFileInd(Message& p_sendMessage,
                               unsigned long long p_bytesInPayload,
                               int& p_clientSocket) const
    {
        ServerSendFileRequestHandler::sendClientSendFileInd(p_sendMessage, p_bytesInPayload, p_clientSocket);
    }
    void sendRequestedFile(std::ifstream& p_fileDescriptor, int& p_clientSocket) const
    {
        ServerSendFileRequestHandler::sendRequestedFile(p_fileDescriptor, p_clientSocket);
    }
};

class ServerSendFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerSendFileRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    void SetUp();
    void TearDown();

    void setExpectationsForSendSeverSendFileResp(int p_clientSocket, Message p_sendline);
    void setExpectationsForSendClientSendFileInd(int p_clientSocket, Message p_sendline);

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    ServerSendFileRequestHandlerTestTable m_sut;
};

void ServerSendFileRequestHandlerTestSuite::SetUp()
{
    testing::internal::CaptureStdout();
}

void ServerSendFileRequestHandlerTestSuite::TearDown()
{
    testing::internal::GetCapturedStdout();
}

void ServerSendFileRequestHandlerTestSuite::setExpectationsForSendSeverSendFileResp(int p_clientSocket,
                                                                                    Message p_sendline)
{
    EXPECT_CALL(*m_unixWrapperMock, send(p_clientSocket,
                                         AllOf(Field(&Message::msgId, p_sendline.msgId),
                                               Field(&Message::numOfMsgInFileTransfer, p_sendline.numOfMsgInFileTransfer),
                                               Field(&Message::bytesInPayload, 0)),
                                         sizeof(Message),
                                         0));
}

void ServerSendFileRequestHandlerTestSuite::setExpectationsForSendClientSendFileInd(int p_clientSocket,
                                                                                    Message p_sendline)
{
    EXPECT_CALL(*m_unixWrapperMock, send(p_clientSocket,
                                         AllOf(Field(&Message::msgId, p_sendline.msgId),
                                               Field(&Message::numOfMsgInFileTransfer, 0),
                                               Field(&Message::bytesInPayload, p_sendline.bytesInPayload)),
                                         sizeof(Message),
                                         0));
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendSeverSendFileRespTest_whenFileLengthIsBellowPayloadSize)
{
    int l_clientSocket = 0;
    unsigned long long l_fileLength = 10;

    Message l_sendline;
    l_sendline.msgId = SERVER_SEND_FILE_RESP;
    l_sendline.numOfMsgInFileTransfer = 1;

    setExpectationsForSendSeverSendFileResp(l_clientSocket, l_sendline);
    m_sut.sendSeverSendFileResp(l_clientSocket, l_fileLength);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendSeverSendFileRespTest_whenFileLengthIsOverallMultipleOfPayloadSize)
{
    int l_clientSocket = 0;
    unsigned long long l_fileLength = 2048;

    Message l_sendline;
    l_sendline.msgId = SERVER_SEND_FILE_RESP;
    l_sendline.numOfMsgInFileTransfer = 2;

    setExpectationsForSendSeverSendFileResp(l_clientSocket, l_sendline);
    m_sut.sendSeverSendFileResp(l_clientSocket, l_fileLength);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendSeverSendFileRespTest_whenFileLengthIsNotOverallMultipleOfPayloadSize)
{
    int l_clientSocket = 0;
    unsigned long long l_fileLength = 2049;

    Message l_sendline;
    l_sendline.msgId = SERVER_SEND_FILE_RESP;
    l_sendline.numOfMsgInFileTransfer = 3;

    setExpectationsForSendSeverSendFileResp(l_clientSocket, l_sendline);
    m_sut.sendSeverSendFileResp(l_clientSocket, l_fileLength);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendClientSendFileIndTest_whenNumberOfValidBytesInPayloadIsLessOrEqualToPayloadSize)
{
    int l_clientSocket = 0;

    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = 250;

    setExpectationsForSendClientSendFileInd(l_clientSocket, l_sendline);
    m_sut.sendClientSendFileInd(l_sendline, l_sendline.bytesInPayload, l_clientSocket);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendClientSendFileIndTest_whenNumberOfValidBytesInPayloadIsGreaterThanPayloadSize)
{
    int l_clientSocket = 0;

    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = 1025;

    EXPECT_DEATH(m_sut.sendClientSendFileInd(l_sendline, l_sendline.bytesInPayload, l_clientSocket), "");
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendRequestedFileTest)
{
    int l_clientSocket = 0;
    std::ifstream l_fileDescriptor = {};

    m_sut.sendRequestedFile(l_fileDescriptor,  l_clientSocket);
}

