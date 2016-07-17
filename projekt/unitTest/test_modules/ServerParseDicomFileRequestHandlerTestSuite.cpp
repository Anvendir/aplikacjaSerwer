#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerParseDicomFileRequestHandler.hpp"
#include "DicomTextInformationExtractorMock.hpp"
#include "DicomBinaryInformationExtractorMock.hpp"
#include "UnixWrapperMock.hpp"

using ::testing::StrictMock;

class ServerParseDicomFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerParseDicomFileRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_dicomTextInformationExtractorMock(std::make_shared<StrictMock<DicomTextInformationExtractorMock>>()),
          m_dicomBinaryInformationExtractorMock(std::make_shared<StrictMock<DicomBinaryInformationExtractorMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    std::shared_ptr<StrictMock<DicomTextInformationExtractorMock>> m_dicomTextInformationExtractorMock;
    std::shared_ptr<StrictMock<DicomBinaryInformationExtractorMock>> m_dicomBinaryInformationExtractorMock;
    ServerParseDicomFileRequestHandler m_sut;
};

TEST_F(ServerParseDicomFileRequestHandlerTestSuite, emptyTest)
{
}

