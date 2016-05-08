#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MessageConverter.hpp"
#include "CommonTypes.h"
#include "ErrorHandlerMock.hpp"

#include <boost/lexical_cast.hpp>
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

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConversionOfMsgIdForIdEqualTo0)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(0);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('0', l_convertedMsg.msgId[0]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[3]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConversionOfMsgIdForIdFrom0To9)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = SERVER_SEND_FILE_REQ;

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('5', l_convertedMsg.msgId[0]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[3]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConversionOfMsgIdForIdFrom10To99)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(37);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('3', l_convertedMsg.msgId[0]);
    ASSERT_EQ('7', l_convertedMsg.msgId[1]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[2]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[3]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConversionOfMsgIdForIdFrom100To999)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(735);

    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);

    ASSERT_EQ('7', l_convertedMsg.msgId[0]);
    ASSERT_EQ('3', l_convertedMsg.msgId[1]);
    ASSERT_EQ('5', l_convertedMsg.msgId[2]);
    ASSERT_EQ('\0', l_convertedMsg.msgId[3]);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testConversionOfMsgIdForIdGreaterThan999)
{
    Message l_inputMsg = {};
    l_inputMsg.msgId = static_cast<EMessageId>(1000);

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    RawMessage l_convertedMsg = m_sut.convertMessageToRawMessage(l_inputMsg);
}

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testNumOfMsgInFileTransferForValueGreaterThan999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.numOfMsgInFileTransfer = 1000000000;

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

TEST_F(MessageConverterFromMessageToRawMessageTestSuite, testBytesInPayloadForValueGreaterThan999999999)
{
    Message l_inputMsg = {};
    l_inputMsg.bytesInPayload = 1000000000;

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
public:
    void initializeRawMessagesWithDefaultValues(RawMessage& p_rawMsg);
};

void MessageConverterFromRawMessageToMessageTestSuite::initializeRawMessagesWithDefaultValues(RawMessage& p_rawMsg)
{
    p_rawMsg = {};

    p_rawMsg.msgId[0] = '1';
    p_rawMsg.numOfMsgInFileTransfer[0] = '0';
    p_rawMsg.bytesInPayload[0] = '1';
    p_rawMsg.payload[0] = 'a';
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdForIdEqualTo0)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = '0';
    l_inputMsg.msgId[1] = '\0';
    l_inputMsg.msgId[2] = '\0';
    l_inputMsg.msgId[3] = '\0';

    Message l_convertedMsg = m_sut.convertRawMessageToMessage(l_inputMsg);

    ASSERT_EQ(CLIENT_WELCOME_MSG_IND, l_convertedMsg.msgId);
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdForIdEqualTo7)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = '7';
    l_inputMsg.msgId[1] = '\0';
    l_inputMsg.msgId[2] = '\0';
    l_inputMsg.msgId[3] = '\0';

    Message l_convertedMsg = m_sut.convertRawMessageToMessage(l_inputMsg);

    ASSERT_EQ(CLIENT_SEND_FILE_IND, l_convertedMsg.msgId);
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdIsFrom10To99)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = '1';
    l_inputMsg.msgId[1] = '4';
    l_inputMsg.msgId[2] = '\0';
    l_inputMsg.msgId[3] = '\0';

    Message l_convertedMsg = m_sut.convertRawMessageToMessage(l_inputMsg);

    ASSERT_EQ(14, l_convertedMsg.msgId);
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdIsFrom100To999)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = '5';
    l_inputMsg.msgId[1] = '2';
    l_inputMsg.msgId[2] = '1';
    l_inputMsg.msgId[3] = '\0';

    Message l_convertedMsg = m_sut.convertRawMessageToMessage(l_inputMsg);

    ASSERT_EQ(521, l_convertedMsg.msgId);
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdWhenEmpty)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = '\0';
    l_inputMsg.msgId[1] = '\0';
    l_inputMsg.msgId[2] = '\0';
    l_inputMsg.msgId[3] = '\0';

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    m_sut.convertRawMessageToMessage(l_inputMsg);
}

TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testConversionOfMsgIdWhenInvalid)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.msgId[0] = 'c';
    l_inputMsg.msgId[1] = 'b';
    l_inputMsg.msgId[2] = 'a';
    l_inputMsg.msgId[3] = '\0';

    EXPECT_CALL(*m_errorHandler, handleHardError(::testing::_));
    m_sut.convertRawMessageToMessage(l_inputMsg);
}

//gdzies pozniej tylko jako przyklad
TEST_F(MessageConverterFromRawMessageToMessageTestSuite, testNumOfMsgInFileTransferForValueEqualTo0)
{
    RawMessage l_inputMsg = {};
    initializeRawMessagesWithDefaultValues(l_inputMsg);
    l_inputMsg.bytesInPayload[0] = '0';
    l_inputMsg.bytesInPayload[1] = '\0';
    l_inputMsg.bytesInPayload[2] = '\0';
    l_inputMsg.bytesInPayload[3] = '\0';
    l_inputMsg.bytesInPayload[4] = '\0';
    l_inputMsg.bytesInPayload[5] = '\0';
    l_inputMsg.bytesInPayload[6] = '\0';
    l_inputMsg.bytesInPayload[7] = '\0';
    l_inputMsg.bytesInPayload[8] = '\0';
    l_inputMsg.bytesInPayload[9] = '\0';

    Message l_convertedMsg = m_sut.convertRawMessageToMessage(l_inputMsg);

    ASSERT_EQ(0, l_convertedMsg.bytesInPayload);
}

