#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "DicomBinaryInformationExtractor.hpp"

class DicomBinaryInformationExtractorTestSuite : public testing::Test
{
public:
    DicomBinaryInformationExtractorTestSuite() : m_sut()
    {

    }
    DicomBinaryInformationExtractor m_sut;
};

TEST_F(DicomBinaryInformationExtractorTestSuite, emptyTest)
{
}
