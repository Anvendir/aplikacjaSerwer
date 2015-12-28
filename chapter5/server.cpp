#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define LISTENQ 1024 /* 2nd argument to listen() */
#define SERV_PORT 9877 /* TCP and UDP */

int Socket(int p_family, int p_type, int p_protocol);
void Bind(int fd, const sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
pid_t Fork(void);
void Close(int fd);

void str_echo(int sockFd);

int main(int argc, char** argv)
{
    int listenFd, connFd;
    pid_t childPid;
    socklen_t cliLen;
    sockaddr_in cliAddr, servAddr;

    listenFd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(SERV_PORT);

    Bind(listenFd, (sockaddr*) &servAddr, sizeof(servAddr));

    Listen(listenFd, LISTENQ);

    for(;;)
    {
        cliLen = sizeof(cliAddr);
        connFd = Accept(listenFd, (sockaddr*) &cliAddr, &cliLen);

        if ((childPid = Fork()) == 0)
        {
            Close(listenFd);
            str_echo(connFd);
            exit(0);
        }
    }
    Close(connFd);

    return 0;
}

