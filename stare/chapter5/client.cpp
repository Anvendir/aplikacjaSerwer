#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <stdlib.h>

#define SERV_PORT 9877 /* TCP and UDP */

int Socket(int p_family, int p_type, int p_protocol);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Inet_pton(int family, const char *strptr, void *addrptr);
void str_cli(FILE *fp, int sockfd);
void err_quit(const char *fmt, ...);

int main(int argc, char **argv)
{
    int sockfd;
    sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: tcpli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (sockaddr*) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);
    exit(0);

    return 0;
}
