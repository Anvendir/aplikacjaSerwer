#include "IUnixWrappers.hpp"
#include "ErrorHandler.hpp"
#include "IMessageConverter.hpp"
#include "MessageConverter.hpp"
#include "CommonTypes.h"
#include <memory>
#include <string>

#pragma once

class UnixWrappers : public IUnixWrappers
{
public:
    UnixWrappers(std::shared_ptr<IErrorHandler> p_errorHandler,
                 std::shared_ptr<IMessageConverter> p_msgConverter = std::make_shared<MessageConverter>());

    void send(int p_socketDescriptor,
              const Message* p_messageToSent,
              size_t p_messageLenghtInBytes = sizeof(RawMessage),
              int p_transmissionType = 0) const override;

    ssize_t recv(int p_socketDescriptor,
                 Message* p_receivedMessage,
                 size_t p_messageLenghtInBytes = sizeof(RawMessage),
                 int p_transmissionType = MSG_WAITALL) const override;

    void close(int p_socketDescriptor) const override;
    pid_t fork(void) const override;
    pid_t getPid() const override;
    std::string executeCommand(const char* p_cmd) const override;

private:
    std::shared_ptr<IErrorHandler> m_error;
    std::shared_ptr<IMessageConverter> m_msgConverter;
};
