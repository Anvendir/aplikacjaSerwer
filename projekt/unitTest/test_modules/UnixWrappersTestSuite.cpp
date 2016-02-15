#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "UnixWrappers.hpp"
#include "ErrorHandlerMock.hpp"

using ::testing::StrictMock;

class UnixWrappersTestSuite : public ::testing::Test
{
public:
    UnixWrappersTestSuite() :
         m_errorHandler(), m_sut(m_errorHandler)
    {

    }

    UnixWrappers m_sut;
    StrictMock<ErrorHandlerMock> m_errorHandler;
};

TEST_F(UnixWrappersTestSuite, fillMe)
{

}

