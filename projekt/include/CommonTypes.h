//Here are collected all common typedefs
#include <sys/socket.h>
#include <netinet/in.h>
#pragma once

typedef sockaddr GenericSockAddr;
typedef sockaddr_in SockAddrIn;

const unsigned int PAYLOAD_SIZE = 1024;

enum EMessageId
{
    CLIENT_WELCOME_MSG_IND,
    SERVER_TEST_FIRST_REQ,
    SERVER_TEST_FIRST_RESP,
    SERVER_TEST_SECOND_REQ,
    SERVER_TEST_SECOND_RESP,
    SERVER_SEND_FILE_REQ,
    SERVER_SEND_FILE_RESP,
    CLIENT_SEND_FILE_IND,
    SERVER_SEND_FILE_LIST_REQ,
    SERVER_SEND_FILE_LIST_RESP
};

struct Message
{
    EMessageId msgId;
    unsigned int numOfMsgInFileTransfer;
    unsigned int bytesInPayload;
    char payload[PAYLOAD_SIZE];

    bool operator==(const Message& A) const
    {
        if(this->msgId == A.msgId and
           this->numOfMsgInFileTransfer == A.numOfMsgInFileTransfer and
           this->bytesInPayload == A.bytesInPayload)
        {
            return true;
        }
        return false;
    }
};

struct RawMessage
{
    char msgId[3];
    char numOfMsgInFileTransfer[10];
    char intbytesInPayload[10];
    char payload[PAYLOAD_SIZE];
};

