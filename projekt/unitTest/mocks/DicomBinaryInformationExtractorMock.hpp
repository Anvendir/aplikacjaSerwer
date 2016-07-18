#include "gmock/gmock.h"
#include "IDicomBinaryInformationExtractor.hpp"

#pragma once

class DicomBinaryInformationExtractorMock : public IDicomBinaryInformationExtractor
{
public:
    MOCK_CONST_METHOD2(extract, bool(const char*, std::string));
};
