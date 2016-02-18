#include "Server.hpp"
#include "ErrorHandler.hpp"
#include "NetworkWrappers.hpp"
#include "UnixWrappers.hpp"

Server::Server()
{
    m_errorHandler = std::make_shared<ErrorHandler>();
    m_networkWrapper = std::make_unique<NetworkWrappers>(m_errorHandler);
    m_unixWrapper = std::make_unique<UnixWrappers>(m_errorHandler);
}

void Server::start() const
{

}

void Server::stop() const
{

}
