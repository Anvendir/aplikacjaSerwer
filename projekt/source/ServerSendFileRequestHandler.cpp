#include "ServerSendFileRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "StreamWrapper.hpp"
#include "IStreamWrapper.hpp"
#include "CommonTypes.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

ServerSendFileRequestHandler::ServerSendFileRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper,
                                                           std::shared_ptr<IStreamWrapper> p_streamWrapper)
    : m_unixWrapper(p_unixWrapper),
      m_inFileDesc(p_streamWrapper)
{

}

void ServerSendFileRequestHandler::handle(int p_clientSocket, const Message p_receivedMsg) const
{
    openGivenFile(p_receivedMsg.payload);
    auto l_fileLength = getFileSize(p_receivedMsg.payload);
    std::cout << "File size: " << l_fileLength << " bytes" << std::endl;

    sendSeverSendFileResp(p_clientSocket, l_fileLength);
    sendRequestedFile(p_clientSocket);

    m_inFileDesc->close();
}

void ServerSendFileRequestHandler::openGivenFile(const std::string& p_filePath) const
{
    m_inFileDesc->open(p_filePath.c_str());

    if (!m_inFileDesc->is_open())
    {
        std::cout << "File " << p_filePath
                  << " is not open. Aplication is going to be terminated"
                  << std::endl;
        exit(-1);
    }
}

unsigned long long ServerSendFileRequestHandler::getFileSize(const std::string& p_filePath) const
{
    m_inFileDesc->seekg(0, m_inFileDesc->end());
    unsigned long long l_fileLength = m_inFileDesc->tellg();
    m_inFileDesc->seekg(0, m_inFileDesc->beg());

    std::cout << "Size of file: " << p_filePath
              << " is equal to: " << l_fileLength
              << " bytes." << std::endl;

    return l_fileLength;
}

unsigned int ServerSendFileRequestHandler::getNumberOfMessagesRequiredToSentGivenBytes(unsigned long long p_numOfBytes) const
{
    if(p_numOfBytes % PAYLOAD_SIZE)
    {
        return p_numOfBytes / PAYLOAD_SIZE + 1;
    }
    else
    {
        return p_numOfBytes / PAYLOAD_SIZE;
    }
}

void ServerSendFileRequestHandler::checkIfReadByteSucceded(int p_byteCounter) const
{
    if(!m_inFileDesc->good())
    {
        std::cout << "Something wrong during reading file, byte number:  "
                  << p_byteCounter << std::endl;
        exit(-1);
    }
}

void ServerSendFileRequestHandler::sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const
{
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_RESP;

    l_sendline.numOfMsgInFileTransfer = getNumberOfMessagesRequiredToSentGivenBytes(p_fileLength);
    m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(Message));
}

void ServerSendFileRequestHandler::sendClientSendFileInd(Message& p_sendMessage,
                                                         unsigned long long p_bytesInPayload,
                                                         int& p_clientSocket) const
{
    if(p_bytesInPayload > PAYLOAD_SIZE)
    {
        std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): "
                  << "Size of valid bytes in payload is greater than payload size!"
                  << std::endl;
        exit(-1);
    }

    p_sendMessage.msgId = CLIENT_SEND_FILE_IND;
    p_sendMessage.bytesInPayload = p_bytesInPayload;
    m_unixWrapper->send(p_clientSocket, &p_sendMessage, sizeof(Message));

    std::cout << "Sent payload bytes: " << sizeof(p_sendMessage.payload)
              << " where valid is: " << p_bytesInPayload << std::endl;
}

void ServerSendFileRequestHandler::sendRequestedFile(int& p_clientSocket) const
{
    unsigned int l_msgCounter = 1;
    unsigned long long l_byteCounter = 0;
    Message l_sendline;
    memset(&l_sendline, 0, sizeof(l_sendline));

    char l_singleByte;
    while(l_singleByte = m_inFileDesc->get())
    {
        checkIfReadByteSucceded(l_byteCounter);
        l_sendline.payload[l_byteCounter] = l_singleByte;
        l_byteCounter++;

        if(l_byteCounter == PAYLOAD_SIZE)
        {
            std::cout << "Sending message number: " << l_msgCounter << std::endl;
            sendClientSendFileInd(l_sendline, l_byteCounter, p_clientSocket);
            l_msgCounter++;

            l_byteCounter = 0;
            memset(&l_sendline, 0, sizeof(l_sendline));
        }
    }

    if(l_byteCounter)
    {
        std::cout << "Sending message number: " << l_msgCounter << std::endl;
        sendClientSendFileInd(l_sendline, l_byteCounter, p_clientSocket);
        l_msgCounter++;
    }
    std::cout << "Sending of file is done!" << std::endl;
}

