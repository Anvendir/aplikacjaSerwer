#include "IDicomBinaryInformationExtractor.hpp"
#include "CommonTypes.h"
#include <string>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

#pragma once

class DicomBinaryInformationExtractor : public IDicomBinaryInformationExtractor
{
public:
    DicomBinaryInformationExtractor();

    bool extract(DcmFileFormat& p_fileFormat, std::string p_textFileName) const override;
private:
    void logFileOpenProblem(std::string p_binaryFileName) const;
};
