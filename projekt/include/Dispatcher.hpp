#include "IDispatcher.hpp"
#include "IErrorHandler.hpp"
#include "IUnixWrappers.hpp"
#include "CommonTypes.h"
#include <memory>

#pragma once

class Dispatcher : public IDispatcher
{
public:
    Dispatcher(std::shared_ptr<IErrorHandler> p_errorHandler);
    void dispatch(int p_clientSocket, const Message p_receivedMsg) const override;

private:
    std::unique_ptr<IUnixWrappers> m_unixWrapper;
};
