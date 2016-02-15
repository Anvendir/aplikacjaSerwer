#include "NetworkWrappers.hpp"

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>

NetworkWrappers::NetworkWrappers(IErrorHandler& p_errorHandler)
    : m_error(p_errorHandler)
{

}

int NetworkWrappers::socket(int p_protocolFamily,
                            int p_socketType,
                            int p_networkProtocol) const
{
    int l_sockFd = ::socket(p_protocolFamily, p_socketType, p_networkProtocol);

    if (l_sockFd < 0)
    {
        m_error.handleHardError("socket error");
    }

    return(l_sockFd);
}

void NetworkWrappers::connect(int p_socketDescriptor,
                              const GenericSockAddr* p_serverAddress,
                              socklen_t p_addressSize) const
{
    if (::connect(p_socketDescriptor, p_serverAddress, p_addressSize) < 0)
    {
        m_error.handleHardError("connect error");
    }
}

void NetworkWrappers::bind(int p_socketDescriptor,
                           const GenericSockAddr* p_serverAddress,
                           socklen_t p_addressSize) const
{
    if (::bind(p_socketDescriptor, p_serverAddress, p_addressSize) < 0)
    {
         m_error.handleHardError("bind error");
    }
}

int NetworkWrappers::accept(int p_socketDescriptor,
                            GenericSockAddr* p_serverAddress,
                            socklen_t* p_addressSize) const
{
    int n;

again:
    if ((n = ::accept(p_socketDescriptor, p_serverAddress, p_addressSize)) < 0)
    {
#ifdef EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif
        {
            goto again;
        }
        else
        {
            m_error.handleHardError("accept error");
        }
    }
    return(n);
}

void NetworkWrappers::listen(int p_socketDescriptor,
                             int p_maxSizeOfConnectionQueue) const
{
    char* l_ptr;

    /* for can ovverride 2nd argument with environment variable */
    if((l_ptr = getenv("LISTENQ")) != NULL)
    {
        p_maxSizeOfConnectionQueue = ::atoi(l_ptr);
    }

    if(::listen(p_socketDescriptor, p_maxSizeOfConnectionQueue) < 0)
    {
        m_error.handleHardError("listen error");
    }
}

const char* NetworkWrappers::ntop(int p_protocolFamily,
                                  const void* p_numericAddresFormat,
                                  char* p_presentationAddressFormat,
                                  size_t p_addressSize) const
{
    const char* l_ptr;

    if (p_presentationAddressFormat == NULL)
    {
        m_error.handleHardError("NULL 3rd argument to inet_ntop");
    }

    if ((l_ptr = inet_ntop(p_protocolFamily,
                           p_numericAddresFormat,
                           p_presentationAddressFormat,
                           p_addressSize)) == NULL)
    {
        m_error.handleHardError("inet_ntop error");
    }

    return(l_ptr);
}

void NetworkWrappers::pton(int p_protocolFamily,
                           const char* p_presentationAddressFormat,
                           void* p_numericAddresFormat) const
{
    int l_result = inet_pton(p_protocolFamily,
                             p_presentationAddressFormat,
                             p_numericAddresFormat);

    char l_errorPredicate[] = "inet_pton error for ";

    if (l_result < 0)
    {
        m_error.handleHardError(strcat(l_errorPredicate,
                                       p_presentationAddressFormat));
    }
    else if (l_result == 0)
    {
        m_error.handleHardError(strcat(l_errorPredicate,
                                       p_presentationAddressFormat));
    }
}

uint32_t NetworkWrappers::htonl(uint32_t p_hostByteOrder) const
{
    return ::htonl(p_hostByteOrder);
}

uint16_t NetworkWrappers::htons(uint16_t p_hostByteOrder) const
{
    return ::htons(p_hostByteOrder);
}

uint32_t NetworkWrappers::ntohl(uint32_t p_networkByteOrder) const
{
    return ::ntohl(p_networkByteOrder);
}

uint16_t NetworkWrappers::ntohs(uint16_t p_networkByteOrder) const
{
    return ::ntohs(p_networkByteOrder);
}
