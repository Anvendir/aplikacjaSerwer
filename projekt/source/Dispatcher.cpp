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
                      << "Case 1: , otrzymana wiadomosc to - " << p_receivedMsg.payload
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
                      << "Case 2: , otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;
            break;
        }
        case SERVER_SEND_FILE_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_SEND_FILE_REQ: otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;

            int l_msgCounter = 0;
            unsigned long long l_byteCounter = 0;
            Message l_sendline;
            memset(&l_sendline, 0, sizeof(l_sendline));

            std::ifstream l_inFileDesc;
            l_inFileDesc.open(p_receivedMsg.payload);

            if (!l_inFileDesc.is_open())
            {
                std::cout << "File " << p_receivedMsg.payload
                          << " is not open. Aplication is going to be terminated"
                          << std::endl;
                exit(-1);
            }

            //rozmiar pliku w bajtach
            l_inFileDesc.seekg (0, l_inFileDesc.end);
            int l_fileLength = l_inFileDesc.tellg();
            l_inFileDesc.seekg (0, l_inFileDesc.beg);
            std::cout << "Size of file: " << p_receivedMsg.payload
                      << " is equal to: " << l_fileLength
                      << " bytes." << std::endl;
            //

            Message l_sendline1;
            int l_temp = l_fileLength / PAYLOAD_SIZE;
            l_sendline1.msgId = SERVER_SEND_FILE_RESP;
            l_sendline1.numOfMsgInFileTransfer = l_fileLength % PAYLOAD_SIZE ? l_temp + 1 : l_temp;
            m_unixWrapper->send(p_clientSocket, &l_sendline1, sizeof(Message));

            char l_singleByte;
            while(l_inFileDesc.get(l_singleByte))
            {
                if(!l_inFileDesc.good())
                {
                    std::cout << "Something wrong during reading file, byte number:  "
                              << l_byteCounter << std::endl;
                    exit(-1);
                }

                l_sendline.payload[l_byteCounter] = l_singleByte;
                l_byteCounter++;

                if(l_byteCounter == PAYLOAD_SIZE)
                {
                    l_sendline.msgId = CLIENT_SEND_FILE_IND;
                    l_sendline.bytesInPayload = l_byteCounter;
                    m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(Message));

                    std::cout << "Message number: " << l_msgCounter << std::endl;

                    /*for(int i = 0; i < PAYLOAD_SIZE; i++)
                    {
                        std::cout << l_sendline.payload[i];
                    }*/
                    std::cout << "Sent bytes: " << sizeof(l_sendline.payload) << std::endl;
                    l_msgCounter++;

                    //zeruj
                    l_byteCounter = 0;
                    memset(&l_sendline, 0, sizeof(l_sendline));
                }
            }

            l_sendline.msgId = CLIENT_SEND_FILE_IND;
            l_sendline.bytesInPayload = l_byteCounter;

            std::cout << l_byteCounter << std::endl;

            std::cout << "Message number: " << l_msgCounter << std::endl;

            m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(Message));

            /*for(int i = 0; i < PAYLOAD_SIZE; i++)
            {
                std::cout << l_sendline.payload[i];
            }*/
            std::cout << "Sent bytes: " << sizeof(l_sendline.payload) << std::endl;
            l_msgCounter++;

            std::cout << "Sending of file is done!" << std::endl;
            std::cout << "File size: " << l_fileLength << " bytes" << std::endl;

            l_inFileDesc.close();

            break;
        }
        default:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Nieznany identyfikator" << std::endl;
            return false;
        }
    }
    return true;
}
