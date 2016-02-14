#include "INetworkWrappers.hpp"
#include "ErrorHandler.hpp"

class NetworkWrappers : public INetworkWrappers
{
public:
    NetworkWrappers(IErrorHandler& p_errorHandler);

    int socket(int p_protocolFamily, int p_socketType, int p_networkProtocol) const override;
    void connect(int p_socketDescriptor, const GenericSockAddr* p_serverAddress, socklen_t p_addressSize) const override;
    void bind(int p_socketDescriptor, const GenericSockAddr* p_serverAddress, socklen_t p_addressSize) const override;
    void listen(int p_socketDescriptor, int p_maxSizeOfConnectionQueue) const override;
    int accept(int p_socketDescriptor, GenericSockAddr* p_serverAddress, socklen_t* p_addressSize) const override;

    const char* ntop(int p_protocolFamily,
                     const void* p_numericAddresFormat,
                     char* p_presentationAddressFormat,
                     size_t p_addressSize) const override;
    void pton(int p_protocolFamily, const char* p_presentationAddressFormat, void* p_numericAddresFormat) const override;

    uint32_t htonl(uint32_t p_hostByteOrder) const override;
    uint16_t htons(uint16_t p_hostByteOrder) const override;
    uint32_t ntohl(uint32_t p_networkByteOrder) const override;
    uint16_t ntohs(uint16_t p_networkByteOrder) const override;

private:
    IErrorHandler& m_error;
};
