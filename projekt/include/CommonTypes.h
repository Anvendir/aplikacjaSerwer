//Here are collected all common typedefs
#include <sys/socket.h>
#include <netinet/in.h>

#pragma once

typedef sockaddr GenericSockAddr;
typedef sockaddr_in SockAddrIn;

const unsigned int PAYLOAD_SIZE = 1024;

enum EMessageId
{
    CLIENT_WELCOME_MSG_IND = 0,
    FIRST_CASE = 1,
    SECOND_CASE = 2,
    SERVER_SEND_FILE_REQ = 3,
    SERVER_SEND_FILE_RESP = 4
};

struct Message
{
    EMessageId msgId;
    unsigned int numOfMsgInFileTransfer;
    unsigned int bytesInPayload;
    char payload[PAYLOAD_SIZE];
};
