#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ServerParseDicomFileRequestHandler.hpp"

class ServerParseDicomFileRequestHandlerTestSuite : public testing::Test
{
public:
    ServerParseDicomFileRequestHandlerTestSuite()
        : m_sut()
    {

    }

    ServerParseDicomFileRequestHandler m_sut;
};

TEST_F(ServerParseDicomFileRequestHandlerTestSuite, emptyTest)
{
}

