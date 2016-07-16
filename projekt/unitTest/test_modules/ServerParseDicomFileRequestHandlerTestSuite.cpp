#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerParseDicomFileRequestHandler.hpp"
#include "UnixWrapperMock.hpp"

using ::testing::StrictMock;

class ServerParseDicomFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerParseDicomFileRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    ServerParseDicomFileRequestHandler m_sut;
};

TEST_F(ServerParseDicomFileRequestHandlerTestSuite, emptyTest)
{
}

