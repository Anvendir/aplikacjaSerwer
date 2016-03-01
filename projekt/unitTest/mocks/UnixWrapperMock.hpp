#include "gmock/gmock.h"
#include "IUnixWrappers.hpp"
#include <iostream>

class UnixWrappersMock : public IUnixWrappers
{
public:
    MOCK_CONST_METHOD4(send, void(int,
                                  const void*,
                                  size_t,
                                  int));
    MOCK_CONST_METHOD4(recv, ssize_t(int,
                                     void*,
                                     size_t,
                                     int));
    MOCK_CONST_METHOD1(close, void(int));
    MOCK_CONST_METHOD0(fork, pid_t(void));
    MOCK_CONST_METHOD0(getPid, pid_t(void));
};
