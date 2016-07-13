#include "IDispatcher.hpp"
#include "IErrorHandler.hpp"
#include "IUnixWrappers.hpp"
#include "IServerSendFileRequestHandler.hpp"
#include "IServerSendFileListRequestHandler.hpp"
#include "IServerParseDicomFileRequestHandler.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class Dispatcher : public IDispatcher
{
public:
    Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper,
               std::shared_ptr<IServerSendFileRequestHandler> p_serverSendFileRequestHandler,
               std::shared_ptr<IServerSendFileListRequestHandler> p_serverSendFileListRequestHandler,
               std::shared_ptr<IServerParseDicomFileRequestHandler> p_serverParseDicomFileRequestHandler);
    bool dispatch(int p_clientSocket, const Message p_receivedMsg) const override;

private:
    void sendServerTestFirstResp(int p_clientSocket) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
    std::shared_ptr<IServerSendFileRequestHandler> m_serverSendFileRequestHandler;
    std::shared_ptr<IServerSendFileListRequestHandler> m_serverSendFileListRequestHandler;
    std::shared_ptr<IServerParseDicomFileRequestHandler> m_serverParseDicomFileRequestHandler;
};
