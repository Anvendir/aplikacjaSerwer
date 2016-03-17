#include "Dispatcher.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"

#include <iostream>
#include <fstream>
#include <cstring>

Dispatcher::Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper)
    : m_unixWrapper(p_unixWrapper)
{

}

bool Dispatcher::dispatch(int p_clientSocket, const Message p_receivedMsg) const
{
    switch(p_receivedMsg.msgId)
    {
        case SERVER_TEST_FIRST_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_TEST_FIRST_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;

            Message l_sendline;
            l_sendline.msgId = SERVER_TEST_FIRST_RESP;
            strcpy(l_sendline.payload, "Odpowiedz");
            m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(l_sendline));
            break;
        }
        case SERVER_TEST_SECOND_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_TEST_SECOND_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;
            break;
        }
        case SERVER_SEND_FILE_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_SEND_FILE_REQ: received message " << p_receivedMsg.payload
                      << std::endl;

            handleServerSendFileRequest(p_clientSocket, p_receivedMsg);
            break;
        }
        default:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Unknown message identyfier" << std::endl;
            return false;
        }
    }
    return true;
}

void Dispatcher::handleServerSendFileRequest(int p_clientSocket, const Message p_receivedMsg) const
{
    std::ifstream l_inFileDesc;

    openGivenFile(l_inFileDesc, p_receivedMsg.payload);
    auto l_fileLength = getFileSize(l_inFileDesc, p_receivedMsg.payload);
    std::cout << "File size: " << l_fileLength << " bytes" << std::endl;

    sendSeverSendFileResp(p_clientSocket, l_fileLength);
    sendRequestedFile(l_inFileDesc, p_clientSocket);

    l_inFileDesc.close();
}

void Dispatcher::openGivenFile(std::ifstream& p_fileDescriptor, const char* p_filePath) const
{
    p_fileDescriptor.open(p_filePath);

    if (!p_fileDescriptor.is_open())
    {
        std::cout << "File " << p_filePath
                  << " is not open. Aplication is going to be terminated"
                  << std::endl;
        exit(-1);
    }
}

unsigned long long Dispatcher::getFileSize(std::ifstream& p_fileDescriptor, const char* p_filePath) const
{
    p_fileDescriptor.seekg (0, p_fileDescriptor.end);
    unsigned long long l_fileLength = p_fileDescriptor.tellg();
    p_fileDescriptor.seekg (0, p_fileDescriptor.beg);

    std::cout << "Size of file: " << p_filePath
              << " is equal to: " << l_fileLength
              << " bytes." << std::endl;

    return l_fileLength;
}

unsigned int Dispatcher::getNumberOfMessagesRequiredToSentGivenBytes(unsigned long long p_numOfBytes) const
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

void Dispatcher::sendSeverSendFileResp(int& p_clientSocket, unsigned long long p_fileLength) const
{
    Message l_sendline;
    l_sendline.msgId = SERVER_SEND_FILE_RESP;

    l_sendline.numOfMsgInFileTransfer = getNumberOfMessagesRequiredToSentGivenBytes(p_fileLength);
    m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(Message));
}

void Dispatcher::sendClientSendFileInd(Message& p_sendMessage,
                                       unsigned long long p_bytesInPayload,
                                       int& p_clientSocket) const
{
    p_sendMessage.msgId = CLIENT_SEND_FILE_IND;
    p_sendMessage.bytesInPayload = p_bytesInPayload;
    m_unixWrapper->send(p_clientSocket, &p_sendMessage, sizeof(Message));
}

void Dispatcher::sendRequestedFile(std::ifstream& p_fileDescriptor, int& p_clientSocket) const
{
    unsigned int l_msgCounter = 0;
    unsigned long long l_byteCounter = 0;
    Message l_sendline;
    memset(&l_sendline, 0, sizeof(l_sendline));

    char l_singleByte;
    while(p_fileDescriptor.get(l_singleByte))
    {
        if(!p_fileDescriptor.good())
        {
            std::cout << "Something wrong during reading file, byte number:  "
                      << l_byteCounter << std::endl;
            exit(-1);
        }

        l_sendline.payload[l_byteCounter] = l_singleByte;
        l_byteCounter++;

        if(l_byteCounter == PAYLOAD_SIZE)
        {
            std::cout << "Sending message number: " << l_msgCounter << std::endl;
            sendClientSendFileInd(l_sendline, l_byteCounter, p_clientSocket);
            std::cout << "Sent payload bytes: " << sizeof(l_sendline.payload)
                      << " where valid is: " << l_byteCounter << std::endl;
            l_msgCounter++;

            l_byteCounter = 0;
            memset(&l_sendline, 0, sizeof(l_sendline));
        }
    }

    std::cout << "Sending message number: " << l_msgCounter << std::endl;
    sendClientSendFileInd(l_sendline, l_byteCounter, p_clientSocket);
    std::cout << "Sent payload bytes: " << sizeof(l_sendline.payload)
              << " where valid is: " << l_byteCounter << std::endl;

    l_msgCounter++;
    std::cout << "Sending of file is done!" << std::endl;
}

