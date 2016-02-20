#include "Server.hpp"
#include "ErrorHandler.hpp"
#include "NetworkWrappers.hpp"
#include "UnixWrappers.hpp"
#include <cstring>

#include <iostream>

Server::Server() :
    m_errorHandler(std::make_shared<ErrorHandler>()),
    m_networkWrapper(std::make_unique<NetworkWrappers>(m_errorHandler)),
    m_unixWrapper(std::make_unique<UnixWrappers>(m_errorHandler))
{

}

void Server::start() const
{
    int l_serverSocket = m_networkWrapper->socket(AF_INET, SOCK_STREAM);
    SockAddrIn l_serverAddrStruct = initializeSocketAddresStructure("192.168.254.1", 9878);

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
    socklen_t l_clientLen = 0;
    int l_clientSocket = 0;
    int l_childPid = 0;
    SockAddrIn l_clientAddrStruct = {};
    static char gowno[128];

    while(true)
    {
        std::cout << "Waiting for connection..." << std::endl;
        l_clientLen = sizeof(l_clientAddrStruct);
        l_clientSocket = m_networkWrapper->accept(p_serverSocket,
                                                  reinterpret_cast<GenericSockAddr*>(&l_clientAddrStruct),
                                                  &l_clientLen);

        if ((l_childPid = m_unixWrapper->fork()) == 0)
        {
            m_unixWrapper->close(p_serverSocket);

            std::cout << "Connection from: "
                      << m_networkWrapper->ntop(AF_INET, &l_clientAddrStruct.sin_addr, gowno, sizeof(gowno))
                      << " and port: "
                      << m_networkWrapper->ntohs(l_clientAddrStruct.sin_port)
                      << std::endl;

            processConnection(l_clientSocket);
            exit(0);
        }

        m_unixWrapper->close(l_clientSocket);
    }
}

SockAddrIn Server::initializeSocketAddresStructure(const char* p_ipAddres, const unsigned int p_portNumber) const
{
    SockAddrIn l_sockAddr;
    memset(&l_sockAddr, 0, sizeof(l_sockAddr));

    l_sockAddr.sin_family = AF_INET;
    l_sockAddr.sin_port = m_networkWrapper->htons(p_portNumber);
    m_networkWrapper->pton(AF_INET, p_ipAddres, &l_sockAddr.sin_addr);

    return l_sockAddr;
}

void Server::processConnection(int p_clientSocket) const
{
	const unsigned int MAXLINE = 4096;
    ssize_t	l_receivedBytes;
	char l_receivedMessage[MAXLINE];

again:
/*	while ((l_receivedBytes = m_unixWrapper->recv(p_clientSocket, l_receivedMessage, MAXLINE)) > 0)
    {
        std::cout << "Otrzymano: " << l_receivedMessage << std::endl;

        const char l_answer[40] = "Potwierdzam otrzymanie";
		m_unixWrapper->send(p_clientSocket, l_answer, strlen(l_answer));
    }*/

    l_receivedBytes = m_unixWrapper->recv(p_clientSocket, l_receivedMessage, MAXLINE, 0);
	if (l_receivedBytes > 0)
    {
        std::cout << "Otrzymano: " << l_receivedMessage << std::endl;

        const char l_answer[40] = "Potwierdzam otrzymanie";
		m_unixWrapper->send(p_clientSocket, l_answer, strlen(l_answer));
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
