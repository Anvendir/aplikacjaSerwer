#include "DicomTextInformationExtractor.hpp"
#include "CommonTypes.h"
#include <iostream>
#include <vector>
#include <utility>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

std::vector<std::pair<std::string, DcmTagKey>> DicomTextInformationExtractor::s_studyDataContainer =
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

DicomTextInformationExtractor::DicomTextInformationExtractor()
{
}

bool DicomTextInformationExtractor::extract(DcmFileFormat& p_fileFormat, std::string p_textFileName) const
{
    std::ofstream l_textFile(p_textFileName);
    if (l_textFile.is_open())
    {
        for(auto l_element: s_studyDataContainer)
        {
            if(not extractSingleInformationElemenFromFile(p_fileFormat, l_textFile, l_element))
            {
                logExtractingProblem(l_element.first);
                l_textFile.close();
                return false;
            }
        }

        l_textFile.close();
        return true;
    }
    else
    {
        logFileOpenProblem(p_textFileName);
        return false;
    }
}

bool DicomTextInformationExtractor::extractSingleInformationElemenFromFile(
    DcmFileFormat& p_fileFormat,
    std::ofstream& p_textFile,
    std::pair<std::string, DcmTagKey> p_dataElementAndName) const
{
    OFString l_patientData;
    if (p_fileFormat.getDataset()->findAndGetOFString(p_dataElementAndName.second, l_patientData).good())
    {
        p_textFile << p_dataElementAndName.first << ": " << l_patientData << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error: cannot access " << p_dataElementAndName.first << "!" << std::endl;
        return false;
    }
}

void DicomTextInformationExtractor::logExtractingProblem(std::string p_elementName) const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "Problem during extracting IE: "
              << p_elementName
              << std::endl;
}

void DicomTextInformationExtractor::logFileOpenProblem(std::string p_textFileName) const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "Couldn't open file: "
              << p_textFileName
              << std::endl;
}
