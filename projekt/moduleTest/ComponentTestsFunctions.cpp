#include "ComponentTests.hpp"

int g_sockfd = 0;
struct sockaddr_in g_servaddr = {};
ssize_t g_receivedBytes = 0;
Message g_receivedMessage = {};

ErrorHandler g_errorHandler = ErrorHandler();
NetworkWrappers g_networkWrapper = NetworkWrappers(std::make_shared<ErrorHandler>(g_errorHandler));
UnixWrappers g_unixWrapper = UnixWrappers(std::make_shared<ErrorHandler>(g_errorHandler));

void initializeConnection(int p_argc, char** p_argv)
{
	if (p_argc != 2)
    {
		g_errorHandler.handleHardError("usage: tcpcli <IPaddress>");
    }

	g_sockfd = g_networkWrapper.socket(AF_INET, SOCK_STREAM, 0);

	bzero(&g_servaddr, sizeof(g_servaddr));
	g_servaddr.sin_family = AF_INET;
	g_servaddr.sin_port = htons(SERV_PORT);
	g_networkWrapper.pton(AF_INET, p_argv[1], &g_servaddr.sin_addr);

	g_networkWrapper.connect(g_sockfd, (GenericSockAddr*)&g_servaddr, sizeof(g_servaddr));
}

void receiveMessageFromServer()
{
    g_receivedBytes = 0;
    g_receivedMessage = {};
again:
	while ((g_receivedBytes = g_unixWrapper.recv(g_sockfd, &g_receivedMessage, MAXLINE, 0)) > 0)
    {
        std::cout << "Otrzymano: " << g_receivedMessage.payload << std::endl;
        break;
    }

	if (g_receivedBytes < 0 && errno == EINTR)
    {
		goto again;
    }
	else if (g_receivedBytes < 0)
    {
		g_errorHandler.handleHardError("processConnection: recv error");
    }
}

//some function wrappers
void Fputs(const char *ptr, FILE *stream)
{
    ErrorHandler g_errorHandler = ErrorHandler();

	if (fputs(ptr, stream) == EOF)
		g_errorHandler.handleHardError("fputs error");
}

char * Fgets(char *ptr, int n, FILE *stream)
{
    ErrorHandler g_errorHandler = ErrorHandler();

	char* rptr;

	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		g_errorHandler.handleHardError("fgets error");

	return (rptr);
}
