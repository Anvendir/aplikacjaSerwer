#include "IDispatcher.hpp"
#include "IErrorHandler.hpp"
#include "IUnixWrappers.hpp"
#include "IServerSendFileRequestHandler.hpp"
#include "ServerSendFileRequestHandler.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class Dispatcher : public IDispatcher
{
public:
    Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper,
               std::shared_ptr<IServerSendFileRequestHandler> p_serverSendFileRequestHandler);
    bool dispatch(int p_clientSocket, const Message p_receivedMsg) const override;

private:
    void sendServerTestFirstResp(int p_clientSocket) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
    std::shared_ptr<IServerSendFileRequestHandler> m_serverSendFileRequestHandler;
};
