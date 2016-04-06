#include "ServerSendFileListRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>

ServerSendFileListRequestHandler::ServerSendFileListRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper)
    : m_unixWrapper(p_unixWrapper)
{

}

void ServerSendFileListRequestHandler::handle(int p_clientSocket, const Message& p_receivedMsg) const
{
}
