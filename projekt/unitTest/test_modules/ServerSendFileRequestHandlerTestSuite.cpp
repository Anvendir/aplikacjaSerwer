#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ServerSendFileRequestHandler.hpp"
#include "UnixWrapperMock.hpp"
#include "StreamWrapperMock.hpp"
#include "StreamWrapper.hpp"

#include <string>
#include <fstream>

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Field;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrEq;

class ServerSendFileRequestHandlerTestTable : public ServerSendFileRequestHandler
{
public:
    ServerSendFileRequestHandlerTestTable(std::shared_ptr<IUnixWrappers> p_unixWrapper,
                                          std::shared_ptr<IStreamWrapper> p_streamWrapper)
        : ServerSendFileRequestHandler(p_unixWrapper, p_streamWrapper)
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
    void sendRequestedFile(int& p_clientSocket) const
    {
        ServerSendFileRequestHandler::sendRequestedFile(p_clientSocket);
    }
};

class ServerSendFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerSendFileRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_streamWrapperMock(std::make_shared<StrictMock<StreamWrapperMock>>()),
          m_sut(m_unixWrapperMock, m_streamWrapperMock)
    {

    }

    void SetUp();
    void TearDown();

    void fillMsgStructForServerSendFileReq(Message& p_msg, const char* p_fileName);
    void setExpectationsForSendSeverSendFileResp(int p_clientSocket, Message p_sendline);
    void setExpectationsForSendClientSendFileInd(int p_clientSocket, Message p_sendline);
    void setExpectationsForGettingSpecifiedNumberOfBytes(int p_numOfBytes);
    void setExpectationsForGetFileSizeFunction(unsigned int p_numberOfReadBytes);
    void setExpectationsForSendSeverSendFileResp(int p_clientSocket);
    void setExpectationsForSendRequestedFile(int p_clientSocket, int p_bytesToSend);

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    std::shared_ptr<StrictMock<StreamWrapperMock>> m_streamWrapperMock;
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

void ServerSendFileRequestHandlerTestSuite::setExpectationsForGettingSpecifiedNumberOfBytes(int p_numOfBytes)
{
    {
        using testing::InSequence;
        InSequence l_sequence;
        EXPECT_CALL(*m_streamWrapperMock, get()).Times(p_numOfBytes)
                                                .WillRepeatedly(Return('c'));
        EXPECT_CALL(*m_streamWrapperMock, get()).WillOnce(Return(0));
    }

    EXPECT_CALL(*m_streamWrapperMock, good()).WillRepeatedly(Return(true));
}

void ServerSendFileRequestHandlerTestSuite::setExpectationsForGetFileSizeFunction(unsigned int p_numberOfReadBytes)
{
    ios_base::seekdir l_seekDirBeg = ios_base::beg;
    ios_base::seekdir l_seekDirEnd = ios_base::end;
    std::fstream l_onlyToMakeWork_toRemoveInFuture;

    EXPECT_CALL(*m_streamWrapperMock, beg()).WillRepeatedly(Return(l_seekDirBeg));
    EXPECT_CALL(*m_streamWrapperMock, seekg(0, l_seekDirBeg))
        .WillRepeatedly(ReturnRef(l_onlyToMakeWork_toRemoveInFuture));
    EXPECT_CALL(*m_streamWrapperMock, tellg()).WillRepeatedly(Return(p_numberOfReadBytes));
    EXPECT_CALL(*m_streamWrapperMock, end()).WillRepeatedly(Return(l_seekDirEnd));
    EXPECT_CALL(*m_streamWrapperMock, seekg(0, l_seekDirEnd))
        .WillRepeatedly(ReturnRef(l_onlyToMakeWork_toRemoveInFuture));
}

void ServerSendFileRequestHandlerTestSuite::fillMsgStructForServerSendFileReq(Message& p_msg,
                                                                              const char* p_fileName)
{
    p_msg.msgId = SERVER_SEND_FILE_REQ;
    strcpy(p_msg.payload, p_fileName);
    p_msg.bytesInPayload = strlen(p_fileName);
}

void ServerSendFileRequestHandlerTestSuite::setExpectationsForSendSeverSendFileResp(int p_clientSocket)
{
    Message l_sendline;
    l_sendline.msgId = SERVER_SEND_FILE_RESP;
    l_sendline.numOfMsgInFileTransfer = 1;

    setExpectationsForSendSeverSendFileResp(p_clientSocket, l_sendline);
}

void ServerSendFileRequestHandlerTestSuite::setExpectationsForSendRequestedFile(int p_clientSocket,
                                                                                int p_bytesToSend)
{
    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = p_bytesToSend;

    setExpectationsForGettingSpecifiedNumberOfBytes(p_bytesToSend);
    setExpectationsForSendClientSendFileInd(p_clientSocket, l_sendline);
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

TEST_F(ServerSendFileRequestHandlerTestSuite, sendRequestedFileTest_whenFirstReadByteIsZero)
{
    int l_clientSocket = 0;
    EXPECT_CALL(*m_streamWrapperMock, get()).WillOnce(Return(0));

    m_sut.sendRequestedFile(l_clientSocket);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendRequestedFileTest_whenInputFileHasOneByteLength)
{
    int l_clientSocket = 0;
    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = 1;

    EXPECT_CALL(*m_streamWrapperMock, get()).Times(2)
                                             .WillOnce(Return('c'))
                                             .WillOnce(Return(0));
    EXPECT_CALL(*m_streamWrapperMock, good()).WillRepeatedly(Return(true));
    setExpectationsForSendClientSendFileInd(l_clientSocket, l_sendline);

    m_sut.sendRequestedFile(l_clientSocket);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendRequestedFileTest_whenInputFileHas1024ByteLength)
{
    int l_clientSocket = 0;
    const int l_numOfBytesInInputFile = 1024;
    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = 1024;

    setExpectationsForGettingSpecifiedNumberOfBytes(l_numOfBytesInInputFile);
    setExpectationsForSendClientSendFileInd(l_clientSocket, l_sendline);

    m_sut.sendRequestedFile(l_clientSocket);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, sendRequestedFileTest_whenInputFileHas1025ByteLength)
{
    int l_clientSocket = 0;
    const int l_numOfBytesInInputFile = 1025;
    Message l_sendline = {};
    l_sendline.msgId = CLIENT_SEND_FILE_IND;
    l_sendline.bytesInPayload = 1024;

    setExpectationsForGettingSpecifiedNumberOfBytes(l_numOfBytesInInputFile);
    setExpectationsForSendClientSendFileInd(l_clientSocket, l_sendline);
    l_sendline.bytesInPayload = 1;
    setExpectationsForSendClientSendFileInd(l_clientSocket, l_sendline);

    m_sut.sendRequestedFile(l_clientSocket);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, handleTestSuccessfulScenario)
{
    int l_clientSocket = 0;
    unsigned int l_sizeOfRequestedFileInBytes = 100;
    const char* l_fileName = "sample.txt";

    Message l_receivedMsg = {};
    fillMsgStructForServerSendFileReq(l_receivedMsg, l_fileName);

    EXPECT_CALL(*m_streamWrapperMock, open(StrEq(l_fileName), _));
    EXPECT_CALL(*m_streamWrapperMock, is_open()).WillRepeatedly(Return(true));
    setExpectationsForGetFileSizeFunction(l_sizeOfRequestedFileInBytes);
    setExpectationsForSendSeverSendFileResp(l_clientSocket);
    setExpectationsForSendRequestedFile(l_clientSocket, l_sizeOfRequestedFileInBytes);
    EXPECT_CALL(*m_streamWrapperMock, close());

    m_sut.handle(l_clientSocket, l_receivedMsg);
}

TEST_F(ServerSendFileRequestHandlerTestSuite, handleTestWhenOpenFileFailed)
{
    int l_clientSocket = 0;
    const char* l_fileName = "sample.txt";

    Message l_receivedMsg = {};
    fillMsgStructForServerSendFileReq(l_receivedMsg, l_fileName);

    EXPECT_CALL(*m_streamWrapperMock, is_open()).WillRepeatedly(Return(false));

    EXPECT_DEATH(m_sut.handle(l_clientSocket, l_receivedMsg), "");
}

