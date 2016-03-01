#include "UnixWrappers.hpp"
#include "NetworkWrappers.hpp"
#include "ErrorHandler.hpp"

#include <memory>
#include <cstring>
#include <iostream>

const int MAXLINE = 4096;
const int SERV_PORT = 9878;

void str_cli(FILE *fp, int sockfd);
void Fputs(const char *ptr, FILE *stream);
char* Fgets(char *ptr, int n, FILE *stream);
void sendSingleMessageTest(int p_argc, char** p_argv);
void exchangingAFewMessagesWithServerTest(int p_argc, char** p_argv);

int main(int argc, char **argv)
{
    //sendSingleMessageTest(argc, argv);
    exchangingAFewMessagesWithServerTest(argc, argv);
	exit(0);
}

void sendSingleMessageTest(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;

    ErrorHandler er = ErrorHandler();
    NetworkWrappers nwr = NetworkWrappers(std::make_shared<ErrorHandler>(er));
    UnixWrappers uwr = UnixWrappers(std::make_shared<ErrorHandler>(er));

	int	sockfd;
	struct sockaddr_in servaddr;

	if (p_argc != 2)
    {
		er.handleHardError("usage: tcpcli <IPaddress>");
    }

	sockfd = nwr.socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	nwr.pton(AF_INET, p_argv[1], &servaddr.sin_addr);

	nwr.connect(sockfd, (GenericSockAddr*)&servaddr, sizeof(servaddr));

    char sendline[MAXLINE] = "Wiadomosc od klienta ;-)", recvline[MAXLINE];
    uwr.send(sockfd, sendline, strlen(sendline));
    uwr.close(sockfd);

    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

void exchangingAFewMessagesWithServerTest(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;

    ErrorHandler er = ErrorHandler();
    NetworkWrappers nwr = NetworkWrappers(std::make_shared<ErrorHandler>(er));
    UnixWrappers uwr = UnixWrappers(std::make_shared<ErrorHandler>(er));

	int	sockfd;
	struct sockaddr_in servaddr;

	if (p_argc != 2)
    {
		er.handleHardError("usage: tcpcli <IPaddress>");
    }

	sockfd = nwr.socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	nwr.pton(AF_INET, p_argv[1], &servaddr.sin_addr);

	nwr.connect(sockfd, (GenericSockAddr*)&servaddr, sizeof(servaddr));

    char recvline[MAXLINE];
    Message sendline = {FIRST_CASE, "Wlazl kotek na plotek..."};

    uwr.send(sockfd, &sendline, sizeof(sendline));

    const unsigned int MAXLINE = 4096;
    ssize_t	l_receivedBytes;
    Message l_receivedMessage = {};
again:
	while ((l_receivedBytes = uwr.recv(sockfd, &l_receivedMessage, MAXLINE, 0)) > 0)
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
		er.handleHardError("processConnection: recv error");
    }

    sendline.msgId = SECOND_CASE;
    strcpy(sendline.payload, "...i mruga...");
    uwr.send(sockfd, &sendline, sizeof(sendline));

    uwr.close(sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

///old functions
void str_cli(FILE *fp, int sockfd)
{
    ErrorHandler er = ErrorHandler();
    UnixWrappers uwr = UnixWrappers(std::make_shared<ErrorHandler>(er));

    char sendline[MAXLINE], recvline[MAXLINE];

    /*while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        uwr.send(sockfd, sendline, strlen(sendline));

        if (uwr.recv(sockfd, recvline, MAXLINE) == 0)
            er.handleHardError("str_cli: server terminated prematurely");

        Fputs(recvline, stdout);
    }*/
}

void Fputs(const char *ptr, FILE *stream)
{
    ErrorHandler er = ErrorHandler();

	if (fputs(ptr, stream) == EOF)
		er.handleHardError("fputs error");
}

char * Fgets(char *ptr, int n, FILE *stream)
{
    ErrorHandler er = ErrorHandler();

	char* rptr;

	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		er.handleHardError("fgets error");

	return (rptr);
}
