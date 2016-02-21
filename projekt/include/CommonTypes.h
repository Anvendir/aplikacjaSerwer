//Here are collected all common typedefs
#include <sys/socket.h>
#include <netinet/in.h>

#pragma once

typedef sockaddr GenericSockAddr;
typedef sockaddr_in SockAddrIn;

struct Message
{
    int msgId;
    char payload[50];
};
