#include "CommonTypes.h"

#pragma once

class IMessageConverter
{
public:

    virtual RawMessage convertMessageToRawMessage(const Message& p_msg) const = 0;
    virtual Message convertRawMessageToMessage(const RawMessage& p_rawMsg) const = 0;
};
