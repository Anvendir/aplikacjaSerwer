#include "IServerSendFileRequestHandler.hpp"
#include "IUnixWrappers.hpp"
#include "IStreamWrapper.hpp"
#include "StreamWrapper.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>

#pragma once

class ServerSendFileRequestHandler : public IServerSendFileRequestHandler
{
public:
    ServerSendFileRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper,
                                 std::shared_ptr<IStreamWrapper> p_streamWrapper = std::make_shared<StreamWrapper>());
    void handle(int p_clientSocket, const Message& p_receivedMsg) const override;

protected:
    void sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const;
    void sendRequestedFile(int& p_clientSocket) const;
    void sendClientSendFileInd(Message& p_sendMessage, unsigned long long p_bytesInPayload, int& p_clientSocket) const;

private:
    void openGivenFile(const std::string& p_filePath) const;
    unsigned long long getFileSize(const std::string& p_filePath) const;
    unsigned int getNumberOfMessagesRequiredToSentGivenBytes(unsigned long long p_numOfBytes) const;
    void checkIfReadByteSucceded(int p_byteCounter) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
    std::shared_ptr<IStreamWrapper> m_inFileDesc;
};
