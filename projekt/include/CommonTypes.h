//Here are collected all common typedefs
#include <sys/socket.h>
#include <netinet/in.h>

#pragma once

typedef sockaddr GenericSockAddr;
typedef sockaddr_in SockAddrIn;

enum EMessageId
{
    FIRST_CASE = 1,
    SECOND_CASE = 2,
};

struct Message
{
    EMessageId msgId;
    char payload[50];
};
