#include "gmock/gmock.h"
#include "IDicomTextInformationExtractor.hpp"

#pragma once

class DicomTextInformationExtractorMock : public IDicomTextInformationExtractor
{
public:
    MOCK_CONST_METHOD2(extract, bool(const char*, std::string));
};
