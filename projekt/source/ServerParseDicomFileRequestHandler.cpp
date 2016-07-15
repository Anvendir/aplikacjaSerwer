#include "ServerParseDicomFileRequestHandler.hpp"
#include "CommonTypes.h"
#include <iostream>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

ServerParseDicomFileRequestHandler::ServerParseDicomFileRequestHandler()
{

}

void ServerParseDicomFileRequestHandler::handle(int p_clientSocket, const Message& p_receivedMsg) const
{
    std::cout << "Helo world" << std::endl;
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile("../../../CT0001.dcm");
    if (status.good())
    {
        OFString patientName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            std::cout << "Patient's Name: " << patientName << std::endl;
        }
        else
            std::cerr << "Error: cannot access Patient's Name!" << std::endl;
    }
    else
        std::cerr << "Error: cannot read DICOM file (" << status.text() << ")" << std::endl;
}

