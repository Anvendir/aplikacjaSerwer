#include "MessageConverter.hpp"
#include "CommonTypes.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

MessageConverter::MessageConverter(std::shared_ptr<IErrorHandler> p_errorHandler)
    : m_error(p_errorHandler)
{

}

void MessageConverter::convertMsgIdToChar(const Message& p_msg, RawMessage& p_rawMsg) const
{
    if(p_msg.msgId > 999)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: msgId of of range!"));
    }

    std::string l_tempString = boost::lexical_cast<std::string>(p_msg.msgId);
    strcpy(p_rawMsg.msgId, l_tempString.c_str());
}

void MessageConverter::convertNumOfMsgInFileTransferToChar(const Message& p_msg, RawMessage& p_rawMsg) const
{
    if(p_msg.numOfMsgInFileTransfer > 999999999)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: numOfMsgInFileTransfer of of range!"));
    }

    std::string l_tempString = boost::lexical_cast<std::string>(p_msg.numOfMsgInFileTransfer);
    strcpy(p_rawMsg.numOfMsgInFileTransfer, l_tempString.c_str());
}

void MessageConverter::convertBytesInPayloadToChar(const Message& p_msg, RawMessage& p_rawMsg) const
{
    if(p_msg.bytesInPayload > PAYLOAD_SIZE)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: bytesInPayload of of range!"));
    }

    std::string l_tempString = boost::lexical_cast<std::string>(p_msg.bytesInPayload);
    strcpy(p_rawMsg.bytesInPayload, l_tempString.c_str());
}

RawMessage MessageConverter::convertMessageToRawMessage(const Message p_msg) const
{
    RawMessage l_rawMsg = {};

    convertMsgIdToChar(p_msg, l_rawMsg);
    convertNumOfMsgInFileTransferToChar(p_msg, l_rawMsg);
    convertBytesInPayloadToChar(p_msg, l_rawMsg);
    memcpy(l_rawMsg.payload, p_msg.payload, p_msg.bytesInPayload);

    return l_rawMsg;
}

void MessageConverter::convertMsgIdToEnum(const RawMessage& p_rawMsg, Message& p_msg) const
{
    try
    {
        unsigned int l_tempInt = boost::lexical_cast<unsigned int>(p_rawMsg.msgId);
        p_msg.msgId = static_cast<EMessageId>(l_tempInt);
    }
    catch (boost::bad_lexical_cast&)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: bad_lexical_cast"));
    }
}

void MessageConverter::convertNumOfMsgInFileTransferToInt(const RawMessage& p_rawMsg, Message& p_msg) const
{
    try
    {
        p_msg.numOfMsgInFileTransfer = boost::lexical_cast<unsigned int>(p_rawMsg.numOfMsgInFileTransfer);
    }
    catch (boost::bad_lexical_cast&)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: bad_lexical_cast"));
    }
}

void MessageConverter::convertBytesInPayloadInt(const RawMessage& p_rawMsg, Message& p_msg) const
{
    try
    {
        p_msg.bytesInPayload = boost::lexical_cast<unsigned int>(p_rawMsg.bytesInPayload);
    }
    catch (boost::bad_lexical_cast&)
    {
        m_error->handleHardError(__FUNCTION__ + std::string(" - error: bad_lexical_cast"));
    }
}

Message MessageConverter::convertRawMessageToMessage(const RawMessage p_rawMsg) const
{
    Message l_msg = {};

    convertMsgIdToEnum(p_rawMsg, l_msg);
    convertNumOfMsgInFileTransferToInt(p_rawMsg, l_msg);
    convertBytesInPayloadInt(p_rawMsg, l_msg);
    memcpy(l_msg.payload, p_rawMsg.payload, l_msg.bytesInPayload);

    return l_msg;
}
