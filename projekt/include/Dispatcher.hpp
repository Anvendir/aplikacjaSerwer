#include "IDispatcher.hpp"
#include "IErrorHandler.hpp"
#include "IUnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class Dispatcher : public IDispatcher
{
public:
    Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper);
    bool dispatch(int p_clientSocket, const Message p_receivedMsg) const override;

private:
    void handleServerSendFileRequest(int p_clientSocket, const Message p_receivedMsg) const;

    void openGivenFile(std::ifstream& p_fileDescriptor, const char* p_filePath) const;
    unsigned long long getFileSize(std::ifstream& p_fileDescriptor, const char* p_filePath) const;
    unsigned int getNumberOfMessagesRequiredToSentGivenBytes(unsigned long long p_numOfBytes) const;

    void sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const;
    void sendRequestedFile(std::ifstream& p_fileDescriptor, int& p_clientSocket) const;
    void sendClientSendFileInd(Message& p_sendMessage, unsigned long long p_bytesInPayload, int& p_clientSocket) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
};
