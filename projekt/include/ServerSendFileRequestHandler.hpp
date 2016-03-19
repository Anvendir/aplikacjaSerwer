#include "IServerSendFileRequestHandler.hpp"
#include "IUnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class ServerSendFileRequestHandler : public IServerSendFileRequestHandler
{
public:
    ServerSendFileRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper);
    void handle(int p_clientSocket, const Message p_receivedMsg) const;

protected:
    void sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const;
    void sendRequestedFile(std::ifstream& p_fileDescriptor, int& p_clientSocket) const;
    void sendClientSendFileInd(Message& p_sendMessage, unsigned long long p_bytesInPayload, int& p_clientSocket) const;

private:
    void openGivenFile(std::ifstream& p_fileDescriptor, const char* p_filePath) const;
    unsigned long long getFileSize(std::ifstream& p_fileDescriptor, const char* p_filePath) const;
    unsigned int getNumberOfMessagesRequiredToSentGivenBytes(unsigned long long p_numOfBytes) const;
    void checkIfReadByteSucceded(std::ifstream& p_fileDescriptor, int p_byteCounter) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
};
