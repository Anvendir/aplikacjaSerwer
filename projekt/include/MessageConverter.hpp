#include "CommonTypes.h"
#include "IMessageConverter.hpp"

#pragma once

class MessageConverter : public IMessageConverter
{
public:

    RawMessage convertMessageToRawMessage(const Message& p_msg) const override;
    Message convertRawMessageToMessage(const RawMessage& p_rawMsg) const override;
};

