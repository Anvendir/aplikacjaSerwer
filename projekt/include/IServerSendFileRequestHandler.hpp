#include "CommonTypes.h"

#pragma once

class IServerSendFileRequestHandler
{
public:
    virtual void handle(int p_clientSocket, const Message& p_receivedMsg) const = 0;
};
