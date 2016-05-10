#include "gmock/gmock.h"
#include "IMessageConverter.hpp"
#include <iostream>

class MessageConverterMock : public IMessageConverter
{
public:
    MOCK_CONST_METHOD1(convertMessageToRawMessage, RawMessage(const Message));
    MOCK_CONST_METHOD1(convertRawMessageToMessage, Message(const RawMessage));
};
