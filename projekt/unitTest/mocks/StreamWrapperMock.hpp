#include "gmock/gmock.h"
#include "IStreamWrapper.hpp"
#include <iostream>

#pragma once

using namespace std;

class StreamWrapperMock : public IStreamWrapper
{
public:
    MOCK_METHOD0(get, char(void));
    MOCK_METHOD0(close, void(void));
    MOCK_METHOD2(open, void(const char*, ios_base::openmode));
    MOCK_CONST_METHOD0(is_open, bool(void));
    MOCK_METHOD2(seekg, istream&(streamoff, ios_base::seekdir));
    MOCK_METHOD0(tellg, streampos(void));
    MOCK_CONST_METHOD0(good, bool(void));
    MOCK_METHOD0(beg, ios_base::seekdir(void));
    MOCK_METHOD0(end, ios_base::seekdir(void));

    virtual ~StreamWrapperMock()
    {
    }
};
