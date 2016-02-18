#include "IServer.hpp"
#include "IErrorHandler.hpp"
#include "INetworkWrappers.hpp"
#include "IUnixWrappers.hpp"

#include <memory>
#pragma once

class Server : public IServer
{
public:
    Server();

    void start() const override;
    void stop() const override;

private:
    std::shared_ptr<IErrorHandler> m_errorHandler;
    std::unique_ptr<INetworkWrappers> m_networkWrapper;
    std::unique_ptr<IUnixWrappers> m_unixWrapper;
};
