#include "IDicomTextInformationExtractor.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

#pragma once

class DicomTextInformationExtractor : public IDicomTextInformationExtractor
{
public:
    DicomTextInformationExtractor();

    bool extract(const char* p_dicomFileName, std::string p_textFileName) const override;
private:
    bool extractDataAndSaveInOutputFile(DcmFileFormat& p_fileFormat, std::string p_textFileName) const;
    bool extractSingleInformationElemenFromFile(DcmFileFormat& p_fileFormat,
                                                std::ofstream& p_textFile,
                                                std::pair<std::string, DcmTagKey> p_dataElementAndName) const;

    void logExtractingProblem(std::string p_elementName) const;
    void logFileOpenProblem(std::string p_textFileName) const;

    static std::vector<std::pair<std::string, DcmTagKey>> s_studyDataContainer;
};
