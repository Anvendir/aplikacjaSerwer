#include "UnixWrappers.hpp"

#include <sys/socket.h>
#include <unistd.h>

UnixWrappers::UnixWrappers(std::shared_ptr<IErrorHandler> p_errorHandler)
    : m_error(p_errorHandler)
{

}

void UnixWrappers::send(int p_socketDescriptor,
                        const void* p_messageToSent,
                        size_t p_messageLenghtInBytes,
                        int p_transmissionType) const
{
	if (::send(p_socketDescriptor, p_messageToSent, p_messageLenghtInBytes, p_transmissionType)
        != static_cast<ssize_t>(p_messageLenghtInBytes))
    {
		m_error->handleHardError("send error");
    }
}

ssize_t UnixWrappers::recv(int p_socketDescriptor,
                           void* p_receivedMessage,
                           size_t p_messageLenghtInBytes,
                           int p_transmissionType) const
{
	ssize_t	l_receivedMessageInBytes;

	if ((l_receivedMessageInBytes = ::recv(p_socketDescriptor,
                                           p_receivedMessage,
                                           p_messageLenghtInBytes,
                                           p_transmissionType)) < 0)
    {
		m_error->handleHardError("recv error");
    }
	return(l_receivedMessageInBytes);
}

void UnixWrappers::close(int p_socketDescriptor) const
{
	if (::close(p_socketDescriptor) == -1)
    {
		m_error->handleHardError("close error");
    }
}

pid_t UnixWrappers::fork(void) const
{
	pid_t l_pidOfTheChildProcess;

	if ((l_pidOfTheChildProcess = ::fork()) == -1)
    {
		m_error->handleHardError("fork error");
    }
	return(l_pidOfTheChildProcess);
}
