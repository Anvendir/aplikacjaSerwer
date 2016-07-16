#include "ServerParseDicomFileRequestHandler.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <iostream>
#include <vector>
#include <utility>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

std::vector<std::pair<std::string, DcmTagKey>> ServerParseDicomFileRequestHandler::s_studyDataContainer =
{
    { "Patient's Name", DCM_PatientName },
    { "Patient's Sex", DCM_PatientSex },
    { "Patient's Birth Data", DCM_PatientBirthDate },
    { "Patient's Age", DCM_PatientAge },
    { "Patient's Weight", DCM_PatientWeight },

    { "Study Date", DCM_StudyDate },
    { "Study Time", DCM_StudyTime },
    { "Study Modality", DCM_Modality },

    { "Manufacturer", DCM_Manufacturer },
    { "DeviceSerialNumber", DCM_DeviceSerialNumber },
    { "Software Version", DCM_SoftwareVersions }
};

ServerParseDicomFileRequestHandler::ServerParseDicomFileRequestHandler(std::shared_ptr<IUnixWrappers> p_unixWrapper)
    : m_unixWrapper(p_unixWrapper), m_textFileName(), m_binaryFileName()
{
}

void ServerParseDicomFileRequestHandler::handle(int p_clientSocket, const Message& p_receivedMsg) const
{
    std::cout << "Handling message ServerParseDicomFileRequest" << std::endl;

    DcmFileFormat l_fileFormat;
    OFCondition l_status = l_fileFormat.loadFile(p_receivedMsg.payload);
    if (l_status.good())
    {
        getInformationFromDicomFile(l_fileFormat);
        sendPositiveResponse(p_clientSocket);
    }
    else
    {
        std::cerr << "Error: cannot read DICOM file (" << l_status.text() << ")" << std::endl;
        sendNegativeResponse(p_clientSocket, l_status.text());
    }
}

void ServerParseDicomFileRequestHandler::getInformationFromDicomFile(DcmFileFormat& p_fileFormat) const
{
    for(auto l_element: s_studyDataContainer)
    {
        getSingleInformationElemenFromFile(p_fileFormat, l_element);
    }
}

void ServerParseDicomFileRequestHandler::getSingleInformationElemenFromFile(
    DcmFileFormat& p_fileFormat,
    std::pair<std::string, DcmTagKey> p_dataElementAndName) const
{
    OFString l_patientData;
    if (p_fileFormat.getDataset()->findAndGetOFString(p_dataElementAndName.second, l_patientData).good())
    {
        std::cout << p_dataElementAndName.first << ": " << l_patientData << std::endl;
    }
    else
    {
        std::cerr << "Error: cannot access " << p_dataElementAndName.first << "!" << std::endl;
    }
}

void ServerParseDicomFileRequestHandler::sendPositiveResponse(int p_clientSocket) const
{
    std::string l_outputFileList = m_textFileName + m_binaryFileName;

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

