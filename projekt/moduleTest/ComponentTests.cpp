#include "UnixWrappers.hpp"
#include "NetworkWrappers.hpp"
#include "ErrorHandler.hpp"

#include <memory>
#include <cstring>
#include <iostream>

//constants
const int MAXLINE = 4096;
const int SERV_PORT = 9878;

//global variables
ErrorHandler g_errorHandler = ErrorHandler();
NetworkWrappers g_networkWrapper = NetworkWrappers(std::make_shared<ErrorHandler>(g_errorHandler));
UnixWrappers g_unixWrapper = UnixWrappers(std::make_shared<ErrorHandler>(g_errorHandler));

int	g_sockfd;
struct sockaddr_in g_servaddr;

//declaration of functions
void Fputs(const char *ptr, FILE *stream);
char* Fgets(char *ptr, int n, FILE *stream);
void exchangingAFewMessagesWithServerTest(int p_argc, char** p_argv);
void initializeConnection(int p_argc, char** p_argv);
void receiveWelcomeMsgFromServer();

int main(int argc, char **argv)
{
    exchangingAFewMessagesWithServerTest(argc, argv);
	exit(0);
}

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

void receiveWelcomeMsgFromServer()
{
    ssize_t	l_receivedBytes_1;
    Message l_receivedMessage_1 = {};

again_1:
	while ((l_receivedBytes_1 = g_unixWrapper.recv(g_sockfd, &l_receivedMessage_1, MAXLINE, 0)) > 0)
    {
        std::cout << "Otrzymano: " << l_receivedMessage_1.payload << std::endl;
        break;
    }

	if (l_receivedBytes_1 < 0 && errno == EINTR)
    {
		goto again_1;
    }
	else if (l_receivedBytes_1 < 0)
    {
		g_errorHandler.handleHardError("processConnection: recv error");
    }
}

void exchangingAFewMessagesWithServerTest(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;

    initializeConnection(p_argc, p_argv);
    receiveWelcomeMsgFromServer();

    char recvline[MAXLINE];
    Message sendline = {FIRST_CASE, "Wlazl kotek na plotek..."};

    g_unixWrapper.send(g_sockfd, &sendline, sizeof(sendline));

    const unsigned int MAXLINE = 4096;
    ssize_t	l_receivedBytes;
    Message l_receivedMessage = {};
again:
	while ((l_receivedBytes = g_unixWrapper.recv(g_sockfd, &l_receivedMessage, MAXLINE, 0)) > 0)
    {
        std::cout << "Otrzymano: " << l_receivedMessage.payload << std::endl;
        break;
    }

	if (l_receivedBytes < 0 && errno == EINTR)
    {
		goto again;
    }
	else if (l_receivedBytes < 0)
    {
		g_errorHandler.handleHardError("processConnection: recv error");
    }

    sendline.msgId = SECOND_CASE;
    strcpy(sendline.payload, "...i mruga...");
    g_unixWrapper.send(g_sockfd, &sendline, sizeof(sendline));

    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
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
