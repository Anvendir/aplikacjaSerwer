#include "CommonTypes.h"

#pragma once

class IDispatcher
{
public:
    virtual void dispatch(int p_clientSocket, const Message p_receivedMsg) const = 0;
};
