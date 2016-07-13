#include "IServerParseDicomFileRequestHandler.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>

#pragma once

class ServerParseDicomFileRequestHandler : public IServerParseDicomFileRequestHandler
{
public:
    ServerParseDicomFileRequestHandler();

    void handle(int p_clientSocket, const Message& p_receivedMsg) const override;
};
