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
    SockAddrIn initializeSocketAddresStructure(const char* p_ipAddres, const unsigned int p_portNumber) const;
    void processConnection(int p_clientSocket) const;
    void waitForConnection(int p_serverSocket) const;

    std::shared_ptr<IErrorHandler> m_errorHandler;
    std::unique_ptr<INetworkWrappers> m_networkWrapper;
    std::unique_ptr<IUnixWrappers> m_unixWrapper;
};
