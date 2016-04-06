#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerSendFileListRequestHandler.hpp"
#include "UnixWrapperMock.hpp"

using ::testing::StrictMock;

class ServerSendFileListRequestHandlerTestSuite : public testing::Test
{
public:
    ServerSendFileListRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    ServerSendFileListRequestHandler m_sut;
};


TEST_F(ServerSendFileListRequestHandlerTestSuite, donapisania)
{
}

