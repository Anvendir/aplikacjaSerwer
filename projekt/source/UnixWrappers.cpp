#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

UnixWrappers::UnixWrappers(std::shared_ptr<IErrorHandler> p_errorHandler,
                           std::shared_ptr<IMessageConverter> p_msgConverter)
    : m_error(p_errorHandler),
      m_msgConverter(p_msgConverter)
{

}

void UnixWrappers::send(int p_socketDescriptor,
                        const Message* p_messageToSent,
                        size_t p_messageLenghtInBytes,
                        int p_transmissionType) const
{
    RawMessage l_rawMsg = m_msgConverter->convertMessageToRawMessage(*p_messageToSent);

	if (::send(p_socketDescriptor,
               &l_rawMsg,
               p_messageLenghtInBytes,
               p_transmissionType) != static_cast<int>(p_messageLenghtInBytes))
    {
		m_error->handleHardError("send error");
    }
}

ssize_t UnixWrappers::recv(int p_socketDescriptor,
                           Message* p_receivedMessage,
                           size_t p_messageLenghtInBytes,
                           int p_transmissionType) const
{
	ssize_t	l_receivedMessageInBytes;
    RawMessage l_rawMsg = {};

	if ((l_receivedMessageInBytes = ::recv(p_socketDescriptor,
                                           &l_rawMsg,
                                           p_messageLenghtInBytes,
                                           p_transmissionType)) < 0)
    {
		m_error->handleHardError("recv error");
    }

    if (l_receivedMessageInBytes > 0)
    {
        *p_receivedMessage = m_msgConverter->convertRawMessageToMessage(l_rawMsg);
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

pid_t UnixWrappers::getPid() const
{
    return ::getpid();
}

std::string UnixWrappers::executeCommand(const char* p_cmd) const
{
    std::shared_ptr<FILE> l_pipe(popen(p_cmd, "r"), pclose);
    if (!l_pipe)
    {
        return "ERROR";
    }

    char l_buffer[128];
    std::string l_result = "";
    while (!feof(l_pipe.get()))
    {
        if (fgets(l_buffer, 128, l_pipe.get()) != NULL)
        {
            l_result += l_buffer;
        }
    }
    return l_result;
}

