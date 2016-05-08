#include "CommonTypes.h"
#include "IMessageConverter.hpp"
#include "ErrorHandler.hpp"
#include <memory>

#pragma once

class MessageConverter : public IMessageConverter
{
public:
    MessageConverter(std::shared_ptr<IErrorHandler> p_errorHandler);

    RawMessage convertMessageToRawMessage(const Message& p_msg) const override;
    Message convertRawMessageToMessage(const RawMessage& p_rawMsg) const override;

private:
    void convertMsgIdToChar(const Message& p_msg, RawMessage& p_rawMsg) const;
    void convertNumOfMsgInFileTransferToChar(const Message& p_msg, RawMessage& p_rawMsg) const;
    void convertBytesInPayloadToChar(const Message& p_msg, RawMessage& p_rawMsg) const;

    void convertMsgIdToEnum(const RawMessage& p_rawMsg, Message& p_msg) const;
    void convertNumOfMsgInFileTransferToInt(const RawMessage& p_rawMsg, Message& p_msg) const;
    void convertBytesInPayloadInt(const RawMessage& p_rawMsg, Message& p_msg) const;

    std::shared_ptr<IErrorHandler> m_error;
};

