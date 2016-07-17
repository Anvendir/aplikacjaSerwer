#include "IServerParseDicomFileRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "DicomTextInformationExtractor.hpp"
#include "DicomBinaryInformationExtractor.hpp"
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
    ServerParseDicomFileRequestHandler(
        std::shared_ptr<IUnixWrappers> p_unixWrapper,
        std::shared_ptr<IDicomTextInformationExtractor> p_dicomTextInformationExtractor = std::make_shared<DicomTextInformationExtractor>(),
        std::shared_ptr<IDicomBinaryInformationExtractor> p_dicomBinaryInformationExtractor = std::make_shared<DicomBinaryInformationExtractor>());

    void handle(int p_clientSocket, const Message& p_receivedMsg) override;
private:
    void parseDicomFile(int p_clientSocket, DcmFileFormat& p_fileFormat) const;
    void sendPositiveResponse(int p_clientSocket) const;
    void sendNegativeResponse(int p_clientSocket, std::string p_cause) const;

    std::shared_ptr<IUnixWrappers> m_unixWrapper;
    std::string m_textFileName;
    std::string m_binaryFileName;
    std::shared_ptr<IDicomTextInformationExtractor> m_dicomTextInformationExtractor;
    std::shared_ptr<IDicomBinaryInformationExtractor> m_dicomBinaryInformationExtractor;
};
