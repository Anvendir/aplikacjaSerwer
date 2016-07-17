#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "DicomTextInformationExtractor.hpp"

class DicomTextInformationExtractorTestSuite : public testing::Test
{
public:
    DicomTextInformationExtractorTestSuite() : m_sut()
    {

    }
    DicomTextInformationExtractor m_sut;
};

TEST_F(DicomTextInformationExtractorTestSuite, emptyTest)
{
}
