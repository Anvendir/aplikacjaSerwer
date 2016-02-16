#include "IUnixWrappers.hpp"
#include "ErrorHandler.hpp"

class UnixWrappers : public IUnixWrappers
{
public:
    UnixWrappers(IErrorHandler& p_errorHandler);

    void send(int p_socketDescriptor,
              const void* p_messageToSent,
              size_t p_messageLenghtInBytes,
              int p_transmissionType = 0) const override;

    ssize_t recv(int p_socketDescriptor,
                 void* p_receivedMessage,
                 size_t p_messageLenghtInBytes,
                 int p_transmissionType = MSG_WAITALL) const override;

    void close(int p_socketDescriptor) const override;
    pid_t fork(void) const override;

private:
    IErrorHandler& m_error;
};
