#include "DicomBinaryInformationExtractor.hpp"
#include "CommonTypes.h"
#include <iostream>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

DicomBinaryInformationExtractor::DicomBinaryInformationExtractor()
{
}

bool DicomBinaryInformationExtractor::extract(DcmFileFormat& p_fileFormat, std::string p_binaryFileName) const
{
    std::ofstream l_binaryFile(p_binaryFileName);
    if (l_binaryFile.is_open())
    {
        l_binaryFile.close();
        return true;
    }
    else
    {
        logFileOpenProblem(p_binaryFileName);
        return false;
    }
}

void DicomBinaryInformationExtractor::logFileOpenProblem(std::string p_binaryFileName) const
{
    std::cout << __FILE__ << ":" << __LINE__
              << "Couldn't open file: "
              << p_binaryFileName
              << std::endl;
}
