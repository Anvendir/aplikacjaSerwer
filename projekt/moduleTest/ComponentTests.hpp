#include "UnixWrappers.hpp"
#include "NetworkWrappers.hpp"
#include "ErrorHandler.hpp"

#include <memory>
#include <cstring>
#include <iostream>

#pragma once

//constants
const int MAXLINE = 4096;
const int SERV_PORT = 9878;

//global variables
extern ErrorHandler g_errorHandler;
extern NetworkWrappers g_networkWrapper;
extern UnixWrappers g_unixWrapper;

extern int g_sockfd;
extern struct sockaddr_in g_servaddr;
extern ssize_t g_receivedBytes;
extern Message g_receivedMessage;

//declaration of functions
void Fputs(const char *ptr, FILE *stream);
char* Fgets(char *ptr, int n, FILE *stream);

void initializeConnection(int p_argc, char** p_argv);
void receiveMessageFromServer();
void receiveMessageFromServer1(std::ofstream& p_outFile);

//testcases
void connectToServer(int p_argc, char** p_argv);
void exchangeAFewSimpleMessagesWithServer(int p_argc, char** p_argv);
void sendFileTransferRequestAndReceiveRequestedFile(int p_argc, char** p_argv);

