#include "CommonTypes.h"

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

#pragma once

class IDicomTextInformationExtractor
{
public:
    virtual bool extract(int p_clientSocket, DcmFileFormat& p_fileFormat, std::string p_textFileName) const= 0;
};
