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

    parseDicomFile(p_clientSocket, p_receivedMsg.payload);
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

void ServerParseDicomFileRequestHandler::parseDicomFile(int p_clientSocket, const char* p_dicomFileName) const
{
    bool l_status = m_dicomTextInformationExtractor->extract(p_dicomFileName, m_textFileName) and
                    m_dicomBinaryInformationExtractor->extract(p_dicomFileName, m_binaryFileName);
    if(l_status)
    {
        sendPositiveResponse(p_clientSocket);
    }
    else
    {
        sendNegativeResponse(p_clientSocket, "Error during data extraction");
    }
}

