#include "Server.hpp"
#include "ErrorHandler.hpp"
#include "NetworkWrappers.hpp"
#include "UnixWrappers.hpp"
#include "Dispatcher.hpp"
#include "ServerSendFileRequestHandler.hpp"
#include "ServerSendFileListRequestHandler.hpp"
#include "ServerParseDicomFileRequestHandler.hpp"
#include <cstring>
#include <iostream>
#include <climits>

Server::Server() :
    m_errorHandler(std::make_shared<ErrorHandler>()),
    m_networkWrapper(std::make_unique<NetworkWrappers>(m_errorHandler)),
    m_unixWrapper(std::make_shared<UnixWrappers>(m_errorHandler)),
    m_dispatcher(std::make_unique<Dispatcher>(m_unixWrapper,
                                              std::make_shared<ServerSendFileRequestHandler>(m_unixWrapper),
                                              std::make_shared<ServerSendFileListRequestHandler>(m_unixWrapper),
                                              std::make_shared<ServerParseDicomFileRequestHandler>(m_unixWrapper)))
{

}

void Server::start() const
{
    int l_serverSocket = m_networkWrapper->socket(AF_INET, SOCK_STREAM);
    //SockAddrIn l_serverAddrStruct = initializeSocketAddresStructure("192.168.254.1", 9878);  /*adres dla modul testow*/
    SockAddrIn l_serverAddrStruct = initializeSocketAddresStructure("192.168.1.8", 9878); /*adres dla Androida */

    m_networkWrapper->bind(l_serverSocket,
                           reinterpret_cast<GenericSockAddr*>(&l_serverAddrStruct),
                           sizeof(l_serverAddrStruct));

    const unsigned int LISTENQ = 10;
    m_networkWrapper->listen(l_serverSocket, LISTENQ);

    waitForConnection(l_serverSocket);
}

void Server::stop() const
{

}

void Server::waitForConnection(int p_serverSocket) const
{
    SockAddrIn l_clientAddrStruct = {};

    while(true)
    {
        std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                  << "Waiting for connection..." << std::endl;

        socklen_t l_clientLen = sizeof(l_clientAddrStruct);
        int l_clientSocket = m_networkWrapper->accept(p_serverSocket,
                                                      reinterpret_cast<GenericSockAddr*>(&l_clientAddrStruct),
                                                      &l_clientLen);

        if (m_unixWrapper->fork() == 0)
        {
            m_unixWrapper->close(p_serverSocket);

            std::cout << "PID: " << m_unixWrapper->getPid() << " | Connection from: "
                      << m_networkWrapper->sockNtop(reinterpret_cast<GenericSockAddr*>(&l_clientAddrStruct))
                      << std::endl;

            processConnection(l_clientSocket);
            exit(0);
        }

        m_unixWrapper->close(l_clientSocket);
    }
}

SockAddrIn Server::initializeSocketAddresStructure(const char* p_ipAddres, const unsigned int p_portNumber) const
{
    SockAddrIn l_sockAddr = {};

    l_sockAddr.sin_family = AF_INET;
    l_sockAddr.sin_port = m_networkWrapper->htons(p_portNumber);
    m_networkWrapper->pton(AF_INET, p_ipAddres, &l_sockAddr.sin_addr);

    return l_sockAddr;
}

void Server::sendWelcomeMessage(int p_clientSocket) const
{
    const std::string l_welcomeMessageContent = "Welcome on server!";
    Message l_welcomeMessage = {};
    l_welcomeMessage.msgId = CLIENT_WELCOME_MSG_IND;
    l_welcomeMessage.bytesInPayload = strlen(l_welcomeMessageContent.c_str()) + 1;
    strcpy(l_welcomeMessage.payload, l_welcomeMessageContent.c_str());

    m_unixWrapper->send(p_clientSocket, &l_welcomeMessage);
}

void Server::processConnection(int p_clientSocket) const
{
	const unsigned int MAXLINE = 4096;
    ssize_t	l_receivedBytes = 0;
	Message l_receivedMessage = {};
    bool l_status = true;

    sendWelcomeMessage(p_clientSocket);

again:
	while ((l_receivedBytes = m_unixWrapper->recv(p_clientSocket, &l_receivedMessage)) > 0)
    {
        l_status = m_dispatcher->dispatch(p_clientSocket, l_receivedMessage);
        if (l_status == false)
        {
		    m_errorHandler->handleHardError("processConnection: dispatching error");
        }
    }

	if (l_receivedBytes < 0 && errno == EINTR)
    {
		goto again;
    }
	else if (l_receivedBytes < 0)
    {
		m_errorHandler->handleHardError("processConnection: recv error");
    }
}
