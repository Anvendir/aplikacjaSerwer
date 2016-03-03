#include "CommonTypes.h"

#include <cstdint>
#include <sys/socket.h>

#pragma once

class INetworkWrappers
{
public:
    virtual int socket(int p_protocolFamily, int p_socketType, int p_networkProtocol = 0) const = 0;
    virtual void connect(int p_socketDescriptor,
                         const GenericSockAddr* p_serverAddress,
                         socklen_t p_addressSize) const = 0;
    virtual void bind(int p_socketDescriptor, const GenericSockAddr* p_serverAddress, socklen_t p_addressSize) const = 0;
    virtual void listen(int p_socketDescriptor, int p_maxSizeOfConnectionQueue) const = 0;
    virtual int accept(int p_socketDescriptor, GenericSockAddr* p_serverAddress, socklen_t* p_addressSize) const = 0;

    virtual const char* ntop(int p_protocolFamily,
                             const void* p_numericAddresFormat,
                             char* p_presentationAddressFormat,
                             size_t p_addressSize) const = 0;
    virtual const char* sockNtop(const GenericSockAddr* p_genericSockAddr) const = 0;

    virtual void pton(int p_protocolFamily,
                      const char* p_presentationAddressFormat,
                      void* p_numericAddresFormat) const = 0;

    virtual uint32_t htonl(uint32_t p_hostByteOrder) const = 0;
    virtual uint16_t htons(uint16_t p_hostByteOrder) const = 0;
    virtual uint32_t ntohl(uint32_t p_networkByteOrder) const = 0;
    virtual uint16_t ntohs(uint16_t p_networkByteOrder) const = 0;

};
