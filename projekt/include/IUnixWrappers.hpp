#include "CommonTypes.h"
#include <string>

#pragma once

class IUnixWrappers
{
public:

    virtual void send(int p_socketDescriptor,
                      const Message* p_messageToSent,
                      size_t p_messageLenghtInBytes = sizeof(RawMessage),
                      int p_transmissionType = 0) const = 0;

    virtual ssize_t recv(int p_socketDescriptor,
                         Message* p_receivedMessage,
                         size_t p_messageLenghtInBytes = sizeof(RawMessage),
                         int p_transmissionType = MSG_WAITALL) const = 0;

    virtual void close(int p_socketDescriptor) const = 0;
    virtual pid_t fork(void) const = 0;
    virtual pid_t getPid(void) const = 0;
    virtual std::string executeCommand(const char* p_cmd) const = 0;

};
