#include "INetworkWrappers.hpp"
#include "ErrorHandler.hpp"

class NetworkWrappers : public INetworkWrappers
{
public:
    NetworkWrappers();

    int socket(int p_protocolFamily, int p_socketType, int p_networkProtocol) override;
    void connect(int p_socketDescriptor, const GenericSockAddr* p_serverAddress, socklen_t p_addressSize) override;
    void bind(int p_socketDescriptor, const GenericSockAddr* p_serverAddress, socklen_t p_addressSize) override;
    void listen(int p_socketDescriptor, int p_maxSizeOfConnectionQueue) override;
    int accept(int p_socketDescriptor, GenericSockAddr* p_serverAddress, socklen_t* p_addressSize) override;

    const char* ntop(int p_protocolFamily, const void* p_numericAddresFormat, char* p_presentationAddressFormat, size_t p_addressSize) override;
    void pton(int p_protocolFamily, const char* p_presentationAddressFormat, void* p_numericAddresFormat) override;

    uint32_t htonl(uint32_t p_hostByteOrder) override;
    uint16_t htons(uint16_t p_hostByteOrder) override;
    uint32_t ntohl(uint32_t p_networkByteOrder) override;
    uint16_t ntohs(uint16_t p_networkByteOrder) override;

private:
    ErrorHandler m_error;
};
