#include "ComponentTests.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <memory>

int g_sockfd = 0;
struct sockaddr_in g_servaddr = {};
ssize_t g_receivedBytes = 0;
Message g_receivedMessage = {};

ErrorHandler g_errorHandler = ErrorHandler();
NetworkWrappers g_networkWrapper = NetworkWrappers(std::make_shared<ErrorHandler>(g_errorHandler));
UnixWrappers g_unixWrapper = UnixWrappers(std::make_shared<ErrorHandler>(g_errorHandler));

//function from main
void runAllTestcases(std::map<std::string, void(*)(char**)>& p_testcaseContainer,
                     char** p_argv)
{
    for (auto l_it = p_testcaseContainer.begin(); l_it != p_testcaseContainer.end(); ++l_it)
    {
        void(*l_testcase)(char**) = *l_it->second;
        (l_testcase)(p_argv);
    }
}

void runSingleTestcase(std::map<std::string, void(*)(char**)>& p_testcaseContainer,
                       char** p_argv)
{
    if(p_testcaseContainer.find(p_argv[2]) == p_testcaseContainer.end())
    {
        std::cout << "Testcase not found!" << std::endl;
    }
    else
    {
        void(*l_testcase)(char**) = p_testcaseContainer.find(p_argv[2])->second;
        (l_testcase)(p_argv);
    }
}

void listAllTestcases(std::map<std::string, void(*)(char**)>& p_testcaseContainer,
                      char** p_argv)
{
    std::cout << "List of all avaliable testcases: " << std::endl;
    for (auto l_it = p_testcaseContainer.begin(); l_it != p_testcaseContainer.end(); ++l_it)
    {
        std::cout << "\t" << l_it->first << std::endl;
    }
}

std::string getUsageMessage(char** p_argv)
{
    std::string l_usageMessage = "Instruction:\n";
    l_usageMessage += "\t- to run all testcases: " + std::string(p_argv[0]) + " <IPaddress>\n";
    l_usageMessage += "\t- to single all testcase: " + std::string(p_argv[0]) +
                      " <IPaddress> <testcaseName>\n";
    l_usageMessage += "\t- to list all testcases: " + std::string(p_argv[0]) + " list\n";

    return l_usageMessage;
}

///helpul
std::string executeCommand(const char* p_cmd)
{
    std::shared_ptr<FILE> l_pipe(popen(p_cmd, "r"), pclose);
    if (!l_pipe)
    {
        return "ERROR";
    }

    char l_buffer[128];
    std::string l_result = "";
    while (!feof(l_pipe.get()))
    {
        if (fgets(l_buffer, 128, l_pipe.get()) != NULL)
        {
            l_result += l_buffer;
        }
    }
    return l_result;
}

void checkIfRequestedAndReceivedFilesMatch(std::string p_file1, std::string p_file2)
{
    std::string l_command = "diff " + p_file1 + " " + p_file2;
    std::string l_resultOfCommand = executeCommand(l_command.c_str());

    if(l_resultOfCommand.empty())
    {
        std::cout << "Requested and received files are equal" << std::endl;
    }
    else
    {
        failTestcase("Requested and received files are not equal!");
        exit(0);
    }
}

void failTestcase(std::string p_message)
{
    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "() - "
              << p_message << std::endl;

}

///testcases functions

void initializeConnection(char** p_argv)
{
	g_sockfd = g_networkWrapper.socket(AF_INET, SOCK_STREAM, 0);

	bzero(&g_servaddr, sizeof(g_servaddr));
	g_servaddr.sin_family = AF_INET;
	g_servaddr.sin_port = htons(SERV_PORT);
	g_networkWrapper.pton(AF_INET, p_argv[1], &g_servaddr.sin_addr);

	g_networkWrapper.connect(g_sockfd, (GenericSockAddr*)&g_servaddr, sizeof(g_servaddr));
}

void receiveMessageFromServer(const int p_msgId)
{
    g_receivedBytes = 0;
    g_receivedMessage = {};
again:
	while ((g_receivedBytes = g_unixWrapper.recv(g_sockfd, &g_receivedMessage, sizeof(Message))) > 0)
    {
        if(g_receivedMessage.msgId != p_msgId)
        {
            std::cout << "Received msg id: " << g_receivedMessage.msgId << std::endl;
            std::cout << "Received bytes: " << g_receivedBytes << std::endl;
            failTestcase("Received message is different than expected!");
            exit(0);
        }
        break;
    }

	if (g_receivedBytes < 0 && errno == EINTR)
    {
		goto again;
    }
	else if (g_receivedBytes < 0)
    {
		g_errorHandler.handleHardError("processConnection: recv error");
    }
}

void receiveMessageClientSendFileIndFromServer(std::ofstream& p_outFile, long long& p_sumOfReceivedBytes)
{
    g_receivedBytes = 0;

    Message l_msg = {};
    memset(&l_msg, 0, sizeof(l_msg));
again:
	while ((g_receivedBytes = g_unixWrapper.recv(g_sockfd, &l_msg, sizeof(Message))) > 0)
    {
        p_sumOfReceivedBytes += g_receivedBytes;
        if(l_msg.msgId != CLIENT_SEND_FILE_IND)
        {
            std::cout << "Received msg id: " << g_receivedMessage.msgId << std::endl;
            std::cout << "Received bytes: " << g_receivedBytes << std::endl;
            failTestcase("Received message is different than expected");
            exit(0);
        }

        for(int i = 0; i < l_msg.bytesInPayload; i++)
        {
            p_outFile << l_msg.payload[i];
        }
        memset(&l_msg, 0, sizeof(l_msg));
        break;
    }

	if (g_receivedBytes < 0 && errno == EINTR)
    {
		goto again;
    }
	else if (g_receivedBytes < 0)
    {
		g_errorHandler.handleHardError("processConnection: recv error");
    }
}

//some function wrappers
void Fputs(const char *ptr, FILE *stream)
{
    ErrorHandler g_errorHandler = ErrorHandler();

	if (fputs(ptr, stream) == EOF)
		g_errorHandler.handleHardError("fputs error");
}

char * Fgets(char *ptr, int n, FILE *stream)
{
    ErrorHandler g_errorHandler = ErrorHandler();

	char* rptr;

	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		g_errorHandler.handleHardError("fgets error");

	return (rptr);
}
