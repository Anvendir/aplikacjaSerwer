#include "CommonTypes.h"

#pragma once

class IServerSendFileRequestHandler
{
public:
    void handle(int p_clientSocket, const Message p_receivedMsg) const;
};
