#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerSendFileRequestHandler.hpp"
#include "UnixWrapperMock.hpp"
#include <string>

using ::testing::StrictMock;
using ::testing::_;

class ServerSendFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerSendFileRequestHandlerTestSuite()
        : m_unixWrapperMock(std::make_shared<StrictMock<UnixWrappersMock>>()),
          m_sut(m_unixWrapperMock)
    {

    }

    std::shared_ptr<StrictMock<UnixWrappersMock>> m_unixWrapperMock;
    ServerSendFileRequestHandler m_sut;
};

TEST_F(ServerSendFileRequestHandlerTestSuite, uzupelnijMnie)
{
}

