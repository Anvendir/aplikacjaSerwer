#include "CommonTypes.h"

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

#pragma once

class IDicomBinaryInformationExtractor
{
public:
    virtual bool extract(DcmFileFormat& p_dicomFileFormat, std::string p_binaryFileName) const= 0;
};
