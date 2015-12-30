#include "NetworkWrappers.hpp"

#include <arpa/inet.h>

NetworkWrappers::NetworkWrappers()
    : m_error() 
{

}

int NetworkWrappers::socket(int p_protocolFamily,
                            int p_socketType,
                            int p_networkProtocol)
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
                              socklen_t p_addressSize)
{
    if (::connect(p_socketDescriptor, p_serverAddress, p_addressSize) < 0)
    {
        m_error.handleHardError("connect error");
    }
}

void NetworkWrappers::bind(int p_socketDescriptor,
                           const GenericSockAddr* p_serverAddress,
                           socklen_t p_addressSize)
{
    if (::bind(p_socketDescriptor, p_serverAddress, p_addressSize) < 0)
    {
         m_error.handleHardError("bind error");
    }
}

int NetworkWrappers::accept(int p_socketDescriptor,
                            GenericSockAddr* p_serverAddress,
                            socklen_t* p_addressSize)
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
                             int p_maxSizeOfConnectionQueue)
{

}

const char* NetworkWrappers::ntop(int p_protocolFamily,
                                  const void* p_numericAddresFormat,
                                  char* p_presentationAddressFormat,
                                  size_t p_addressSize)
{

}

void NetworkWrappers::pton(int p_protocolFamily,
                           const char* p_presentationAddressFormat,
                           void* p_numericAddresFormat)
{

}

uint32_t NetworkWrappers::htonl(uint32_t p_hostByteOrder)
{
    return ::htonl(p_hostByteOrder);
}

uint16_t NetworkWrappers::htons(uint16_t p_hostByteOrder)
{
    return ::htons(p_hostByteOrder);
}

uint32_t NetworkWrappers::ntohl(uint32_t p_networkByteOrder)
{
    return ::ntohl(p_networkByteOrder);
}

uint16_t NetworkWrappers::ntohs(uint16_t p_networkByteOrder)
{
    return ::ntohs(p_networkByteOrder);
}
