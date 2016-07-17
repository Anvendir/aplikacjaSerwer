#include "gmock/gmock.h"
#include "IServerParseDicomFileRequestHandler.hpp"

#pragma once

class ServerParseDicomFileRequestHandlerMock : public IServerParseDicomFileRequestHandler
{
public:
    MOCK_METHOD2(handle, void(int, const Message&));
};
