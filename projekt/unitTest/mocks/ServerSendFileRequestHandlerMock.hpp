#include "gmock/gmock.h"
#include "IServerSendFileRequestHandler.hpp"

#pragma once

class ServerSendFileRequestHandlerMock : public IServerSendFileRequestHandler
{
public:
    MOCK_CONST_METHOD2(handle, void(int, const Message&));
};
