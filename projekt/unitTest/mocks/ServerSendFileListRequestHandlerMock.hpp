#include "gmock/gmock.h"
#include "IServerSendFileListRequestHandler.hpp"

#pragma once

class ServerSendFileListRequestHandlerMock : public IServerSendFileListRequestHandler
{
public:
    MOCK_CONST_METHOD2(handle, void(int, const Message&));
};
