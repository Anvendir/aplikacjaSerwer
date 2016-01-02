#include <sys/socket.h>
#include <sys/errno.h>

#include <cstdarg>
#include <syslog.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /* max text line length */

void err_sys(const char *fmt, ...);
void err_quit(const char *fmt, ...);
char* Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);

/* Write "n" bytes to a descriptor. */
ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = (char *) vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; /* and call write() again */
            else
                return(-1); /* error */
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return(n);
}
/* end writen */

void Writen(int fd, void *ptr, size_t nbytes)
{
    if (writen(fd, ptr, nbytes) != nbytes)
        err_sys("writen error");
}

static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static char *read_ptr;
    static char read_buf[MAXLINE];

    if (read_cnt <= 0)
    {
    again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
        {
            if (errno == EINTR)
                goto again;
            return(-1);
        }
        else if (read_cnt == 0)
            return(0);
        read_ptr = read_buf;
    }
    
    read_cnt--;
    *ptr = *read_ptr++;
    return(1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = (char*)vptr;
    for (n = 1; n < maxlen; n++)
    {
        if ((rc = my_read(fd, &c)) == 1)
        {
            *ptr++ = c;
            if (c == '\n')
                break;  /* newline is stored, like fgets() */
        }
        else if (rc == 0)
        {
            *ptr = 0;
            return(n - 1);  /* EOF, n - 1 bytes were read */
        }
        else
            return(-1);     /* error, errno set by read() */
    }

    *ptr = 0;   /* null terminate like fgets() */
    return(n);
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n;

    if ( (n = readline(fd, ptr, maxlen)) < 0)
        err_sys("readline error");

    return(n);
}

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Writen(sockfd, sendline, strlen(sendline));

        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("strl_cli: server terminated prematurely");

        Fputs(recvline, stdout);
    }
}

void str_echo(int sockFd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while ((n = read(sockFd, buf, MAXLINE)) > 0)
    {
        Writen(sockFd, buf, n);
    }

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}

pid_t Fork(void)
{
    pid_t pid;

    if ( (pid = fork()) == -1)
        err_sys("fork error");
    return(pid);
}

void Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}

int Socket(int p_family, int p_type, int p_protocol)
{
    int n;
    if ((n = socket(p_family, p_type, p_protocol)) < 0)
    {
        err_sys("socket error");
    }
    return(n);
}

void Bind(int fd, const sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

void Listen(int fd, int backlog)
{
    char *ptr;

    /* 4can ovverride 2nd argument with environment variable */
    if((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if(listen(fd, backlog) < 0)
        err_sys("listen error");
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

again:
    if ( (n = accept(fd, sa, salenptr)) < 0)
    {
#ifdef EPROTO
    if (errno == EPROTO || errno == ECONNABORTED)
#else
    if (errno == ECONNABORTED)
#endif
        goto again;
    else
        err_sys("accept error");
    }
    return(n);
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        err_sys("connect error");
}

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
    const char* ptr;

    if (strptr == NULL) /* check for old code */
        err_quit("NULL 3rd argument to inet_ntop");

    if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
        err_sys("inet_ntop error");     /* sets errno */

    return(ptr);
}

void Inet_pton(int family, const char *strptr, void *addrptr)
{
    int n;

    if ((n = inet_pton(family, strptr, addrptr)) < 0)
        err_sys("inet_pton error for %s", strptr);  /* errno set */
    else if (n == 0)
        err_quit("inet_pton error for %s", strptr); /* errno not set */
}

char* Fgets(char *ptr, int n, FILE *stream)
{
    char* rptr;

    if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
        err_sys("fgets error");

    return (rptr);
}

void Fputs(const char *ptr, FILE *stream)
{
    if (fputs(ptr, stream) == EOF)
        err_sys("fputs error");
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE + 1];

    errno_save = errno; /* value caller might want printed */
#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap); /* safe */
#else
    vsprintf(buf, fmt, ap);
#endif
    n = strlen(buf);

    if(errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    int daemon_proc; /* set nonzero by daemon_init() */
    if(daemon_proc)
    {
        syslog(level, buf);
    }
    else
    {
        fflush(stdout); /* in case stdout and stderr are the same */
        fputs(buf, stderr);
        fflush(stderr);
    }
    return;
}

/* Fatal error related to system call
 * Print message and terminate */

void err_sys(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

/* Fatal error unrelated to system call
 * Print message and terminate */

void err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}
