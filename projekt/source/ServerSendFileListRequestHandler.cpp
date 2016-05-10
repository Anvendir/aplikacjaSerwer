#include "ServerSendFileListRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>
#include <cstring>
#include <cstdio>

ServerSendFileListRequestHandler::ServerSendFileListRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper)
    : m_unixWrapper(p_unixWrapper)
{

}

void ServerSendFileListRequestHandler::handle(int p_clientSocket, const Message& p_receivedMsg) const
{
    std::string l_fileList = getFileList();
    if (l_fileList == "ERROR")
    {
        l_fileList = "";
    }
    sendServerFileListRequestResponse(p_clientSocket, l_fileList);
}

std::string ServerSendFileListRequestHandler::getFileList() const
{
    std::string l_repositoryRootPath = m_unixWrapper->executeCommand("git rev-parse --show-toplevel");

    if(l_repositoryRootPath == "ERROR")
    {
        return l_repositoryRootPath;
    }

    l_repositoryRootPath.back() = '/';
    std::string l_filesPath = l_repositoryRootPath + "projekt/moduleTest/plikiPrzykladowe/";

    return m_unixWrapper->executeCommand(("ls " + l_filesPath).c_str());
}

void ServerSendFileListRequestHandler::sendServerFileListRequestResponse(int p_clientSocket, std::string p_fileList) const
{
    Message l_msg = {};
    l_msg.msgId = SERVER_SEND_FILE_LIST_RESP;
    l_msg.bytesInPayload = p_fileList.size();
    strcpy(l_msg.payload, p_fileList.c_str());

    m_unixWrapper->send(p_clientSocket, &l_msg);
}
