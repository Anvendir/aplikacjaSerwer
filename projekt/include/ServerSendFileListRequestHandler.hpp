#include "IServerSendFileListRequestHandler.hpp"
#include "IUnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>

#pragma once

class ServerSendFileListRequestHandler : public IServerSendFileListRequestHandler
{
public:
    ServerSendFileListRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper);
    void handle(int p_clientSocket, const Message& p_receivedMsg) const override;

private:
    void sendServerFileListRequestResponse(int p_clientSocket, std::string p_fileList) const;
    std::string getFileList() const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
};
