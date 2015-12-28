#include <sys/socket.h>
#include <sys/errno.h>

#include <cstdarg>
#include <syslog.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

#include <unistd.h>

#define MAXLINE 4096 /* max text line length */

void err_sys(const char *fmt, ...);

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
