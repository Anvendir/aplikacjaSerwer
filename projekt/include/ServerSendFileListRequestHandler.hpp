#include "IServerSendFileListRequestHandler.hpp"
#include "IUnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class ServerSendFileListRequestHandler : public IServerSendFileListRequestHandler
{
public:
    ServerSendFileListRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper);
    void handle(int p_clientSocket, const Message& p_receivedMsg) const override;

private:
    std::shared_ptr<IUnixWrappers> m_unixWrapper;
};
