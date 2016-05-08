#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MessageConverter.hpp"

using ::testing::StrictMock;

class MessageConverterTestSuite : public ::testing::Test
{
public:
    MessageConverterTestSuite() :
         m_sut()
    {

    }

    MessageConverter m_sut;
};

TEST_F(MessageConverterTestSuite, Blabla)
{
}

