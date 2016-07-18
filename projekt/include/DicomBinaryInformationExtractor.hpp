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

    bool extract(const char* p_dicomFileName, std::string p_textFileName) const override;
private:
    bool processFile(FILE*& p_binaryFile, std::string p_fileName) const;
    bool loadDicomFile(DcmFileFormat*& p_dicomFile, std::string p_fileName) const;
    bool loadDicomImage(DicomImage*& p_image, DcmFileFormat*& p_dfile) const;
    void saveImageAsPngFile(FILE*& p_binaryFile, DicomImage*& p_image) const;

    void logFileOpenProblem(std::string p_binaryFileName) const;
    void logLackOfLoadedDictionary() const;
    void logProblemWithLoadingDicomFile(DicomImage* p_image) const;
};
