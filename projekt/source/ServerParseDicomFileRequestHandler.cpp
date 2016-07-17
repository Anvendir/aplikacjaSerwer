#include "ServerParseDicomFileRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "DicomTextInformationExtractor.hpp"
#include "DicomBinaryInformationExtractor.hpp"
#include "CommonTypes.h"
#include <iostream>
#include <vector>
#include <utility>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

ServerParseDicomFileRequestHandler::ServerParseDicomFileRequestHandler(
    std::shared_ptr<IUnixWrappers> p_unixWrapper,
    std::shared_ptr<IDicomTextInformationExtractor> p_dicomTextInformationExtractor,
    std::shared_ptr<IDicomBinaryInformationExtractor> p_dicomBinaryInformationExtractor)
  : m_unixWrapper(p_unixWrapper),
    m_textFileName(),
    m_binaryFileName(),
    m_dicomTextInformationExtractor(p_dicomTextInformationExtractor),
    m_dicomBinaryInformationExtractor(p_dicomBinaryInformationExtractor)
{
}

void ServerParseDicomFileRequestHandler::handle(int p_clientSocket, const Message& p_receivedMsg)
{
    std::cout << "Handling message ServerParseDicomFileRequest" << std::endl;
    m_textFileName = std::string(p_receivedMsg.payload) + ".txt";
    m_binaryFileName = std::string(p_receivedMsg.payload) + ".png";

    DcmFileFormat l_fileFormat;
    OFCondition l_status = l_fileFormat.loadFile(p_receivedMsg.payload);
    if (l_status.good())
    {
        parseDicomFile(p_clientSocket, l_fileFormat);
    }
    else
    {
        std::cerr << "Error: cannot read DICOM file (" << l_status.text() << ")" << std::endl;
        sendNegativeResponse(p_clientSocket, l_status.text());
    }
}

void ServerParseDicomFileRequestHandler::sendPositiveResponse(int p_clientSocket) const
{
    std::string l_outputFileList = m_textFileName + " " + m_binaryFileName;

    Message l_msg = {};
    l_msg.msgId = SERVER_PARSE_DICOM_FILE_RESP;
    l_msg.bytesInPayload = strlen(l_outputFileList.c_str());
    strcpy(l_msg.payload, l_outputFileList.c_str());

    m_unixWrapper->send(p_clientSocket, &l_msg);
}

void ServerParseDicomFileRequestHandler::sendNegativeResponse(int p_clientSocket, std::string p_cause) const
{
    std::string l_negativeAnswer = "Message status NOK - " + p_cause;
    Message l_msg = {};
    l_msg.msgId = SERVER_PARSE_DICOM_FILE_RESP;
    l_msg.bytesInPayload = strlen(l_negativeAnswer.c_str());
    strcpy(l_msg.payload, l_negativeAnswer.c_str());

    m_unixWrapper->send(p_clientSocket, &l_msg);
}

void ServerParseDicomFileRequestHandler::parseDicomFile(int p_clientSocket, DcmFileFormat& p_fileFormat) const
{
    bool l_status = m_dicomTextInformationExtractor->extract(p_fileFormat, m_textFileName) and
                    m_dicomBinaryInformationExtractor->extract(p_fileFormat, m_binaryFileName);
    if(l_status)
    {
        sendPositiveResponse(p_clientSocket);
    }
    else
    {
        sendNegativeResponse(p_clientSocket, "Error during data extraction");
    }
}

