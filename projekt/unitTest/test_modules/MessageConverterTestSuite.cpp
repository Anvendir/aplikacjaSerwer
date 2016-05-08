#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MessageConverter.hpp"
#include "CommonTypes.h"
#include "ErrorHandlerMock.hpp"

#include <cstring>

using ::testing::StrictMock;

class MessageConverterTestSuite : public ::testing::Test
{
public:
    MessageConverterTestSuite() :
         m_errorHandler(std::make_shared<StrictMock<ErrorHandlerMock>>()),
         m_sut(m_errorHandler)
    {

    }

    std::shared_ptr<StrictMock<ErrorHandlerMock>> m_errorHandler;
    MessageConverter m_sut;
};

/*
 * Testcases for convertions from Message to RawMessage
 */

class MessageConverterFromMessageToRawMessageTestSuite : public MessageConverterTestSuite
{
};

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, tesConversionOfmsgIdForIdEqualTo0)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(0);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('0', l_convertedMsg.msgId[0]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, tesConversionOfmsgIdForIdFrom0To9)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = SERVER_SEND_FILE_REQ;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('5', l_convertedMsg.msgId[0]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, tesConversionOfmsgIdForIdFrom10To99)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(37);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('3', l_convertedMsg.msgId[0]);
    ASSERT_EQ('7', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, tesConversionOfmsgIdForIdFrom100To999)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(735);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('7', l_convertedMsg.msgId[0]);
    ASSERT_EQ('3', l_convertedMsg.msgId[1]);
    ASSERT_EQ('5', l_convertedMsg.msgId[2]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, tesConversionOfmsgIdForIdGreaterThan999)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(1000);

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueGreaterThan4000000000)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 4000000001;

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueIsEqualTo0)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 0;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('0', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom0To9)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 2;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom10To99)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 14;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom100To999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 536;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom1000To9999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 3338;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('8', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom10000To99999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 12345;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom100000To999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 123456;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom1000000To9999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 1234567;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('7', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom10000000To99999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 12345670;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('7', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom100000000To999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 123456701;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('7', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueFrom1000000000To9999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 1234567012;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('3', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('4', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('5', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('6', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('7', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('2', l_convertedMsg.numOfMsgInFileTransfer[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueGreaterThan4000000000)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 4000000001;

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueIsEqualTo0)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 0;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('0', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom0To9)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 2;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom10To99)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 14;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom100To999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 536;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom1000To9999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 3338;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('8', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom10000To99999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 12345;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom100000To999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 123456;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom1000000To9999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 1234567;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('7', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom10000000To99999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 12345670;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('7', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom100000000To999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 123456701;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('7', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueFrom1000000000To9999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 1234567012;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('3', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('4', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('5', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('6', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('7', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('2', l_convertedMsg.bytesInPayload[9]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConvertMessageToRawMessageAsAWhole)
{
    std::string l_payload = "Welcome on Server!";

    Message l_inputMsg;
    l_inputMsg.msgId = SERVER_SEND_FILE_REQ;
    l_inputMsg.numOfMsgInFileTransfer = 10;
    l_inputMsg.bytesInPayload = strlen(l_payload.c_str());
    strcpy(l_inputMsg.payload, l_payload.c_str());

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('5', l_convertedMsg.msgId[0]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);

    ASSERT_EQ('1', l_convertedMsg.numOfMsgInFileTransfer[0]);
    ASSERT_EQ('0', l_convertedMsg.numOfMsgInFileTransfer[1]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[2]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[3]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[4]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[5]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[6]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[7]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[8]);
    ASSERT_EQ('\0', l_convertedMsg.numOfMsgInFileTransfer[9]);

    ASSERT_EQ('1', l_convertedMsg.bytesInPayload[0]);
    ASSERT_EQ('8', l_convertedMsg.bytesInPayload[1]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[2]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[3]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[4]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[5]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[6]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[7]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[8]);
    ASSERT_EQ('\0', l_convertedMsg.bytesInPayload[9]);

    ASSERT_STREQ(l_inputMsg.payload, l_convertedMsg.payload);
}

/*
 * Testcases for convertions from RawMessage to Message
 */

class MessageConverterFromRawMessageToMessageTestSuite : public MessageConverterTestSuite
{
};

