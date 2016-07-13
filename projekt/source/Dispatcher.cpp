#include "Dispatcher.hpp"
#include "UnixWrappers.hpp"
#include "IServerSendFileRequestHandler.hpp"
#include "IServerSendFileListRequestHandler.hpp"
#include "IServerParseDicomFileRequestHandler.hpp"
#include "CommonTypes.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <cstring>

Dispatcher::Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper,
                       std::shared_ptr<IServerSendFileRequestHandler> p_serverSendFileRequestHandler,
                       std::shared_ptr<IServerSendFileListRequestHandler> p_serverSendFileListRequestHandler,
                       std::shared_ptr<IServerParseDicomFileRequestHandler> p_serverParseDicomFileRequestHandler)
    : m_unixWrapper(p_unixWrapper),
      m_serverSendFileRequestHandler(p_serverSendFileRequestHandler),
      m_serverSendFileListRequestHandler(p_serverSendFileListRequestHandler),
      m_serverParseDicomFileRequestHandler(p_serverParseDicomFileRequestHandler)
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

            sendServerTestFirstResp(p_clientSocket);
            break;
        }
        case SERVER_TEST_SECOND_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_TEST_SECOND_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;
            break;
        }
        case SERVER_SEND_FILE_LIST_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_SEND_FILE_LIST_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;
            m_serverSendFileListRequestHandler->handle(p_clientSocket, p_receivedMsg);
            break;
        }
        case SERVER_SEND_FILE_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_SEND_FILE_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;

            m_serverSendFileRequestHandler->handle(p_clientSocket, p_receivedMsg);
            break;
        }
        case SERVER_PARSE_DICOM_FILE_REQ:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case SERVER_PARSE_DICOM_FILE_REQ: received message - " << p_receivedMsg.payload
                      << std::endl;

            m_serverParseDicomFileRequestHandler->handle(p_clientSocket, p_receivedMsg);
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

void Dispatcher::sendServerTestFirstResp(int p_clientSocket) const
{
    std::string l_msgContent = "Odpowiedz";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_TEST_FIRST_RESP;
    l_sendline.bytesInPayload = strlen(l_msgContent.c_str()) + 1;
    strcpy(l_sendline.payload, l_msgContent.c_str());
    m_unixWrapper->send(p_clientSocket, &l_sendline);
}
