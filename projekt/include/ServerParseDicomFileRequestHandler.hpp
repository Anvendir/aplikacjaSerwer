#include "IServerParseDicomFileRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

#pragma once

class ServerParseDicomFileRequestHandler : public IServerParseDicomFileRequestHandler
{
public:
    ServerParseDicomFileRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper);

    void handle(int p_clientSocket, const Message& p_receivedMsg) const override;
private:
    void getInformationFromDicomFile(DcmFileFormat& p_fileFormat) const;
    void getSingleInformationElemenFromFile(DcmFileFormat& p_fileFormat,
                                            std::pair<std::string, DcmTagKey> p_dataElementAndName) const;
    void sendPositiveResponse(int p_clientSocket) const;
    void sendNegativeResponse(int p_clientSocket, std::string p_cause) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
    static std::vector<std::pair<std::string, DcmTagKey>> s_studyDataContainer;
    std::string m_textFileName;
    std::string m_binaryFileName;
};
