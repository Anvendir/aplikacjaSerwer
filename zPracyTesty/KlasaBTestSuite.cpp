#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

#include "KlasaB.hpp"
#include "KlasaAMock.hpp"

using namespace testing;
using namespace std;

class KlasaBTestSuite : public Test
{
public:
    KlasaBTestSuite() : klasaAMock(), sut(klasaAMock)
    {

    }

    StrictMock<KlasaAMock> klasaAMock;   
    KlasaB sut;
};


TEST_F(KlasaBTestSuite, testA)
{
    EXPECT_CALL(klasaAMock, dodaj(3, 4)).WillOnce(Return(5));
    int a = sut.huj();
    cout << a << endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
