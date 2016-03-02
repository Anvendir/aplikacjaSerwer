#include "ComponentTests.hpp"

int main(int argc, char **argv)
{
    void (*testcasesList[])(int, char**) = {connectToServer, exchangeAFewSimpleMessagesWithServer};

    for(auto i : testcasesList)
    {
        std::cout << std::endl;
        (*i)(argc, argv);
    }

	exit(0);
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive welcome message from server
 * Step3: Close connection
**************************************************************************/

void connectToServer(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argc, p_argv);
//Step2
    receiveMessageFromServer();
//Step3
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive welcome message from server
 * Step3: Send message FRIST_CASE to the server
 * Step4: Receive message form server
 * Step5: Send message SECOND_CASE to the server
 * Step6: Close connection
**************************************************************************/

void exchangeAFewSimpleMessagesWithServer(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argc, p_argv);
//Step2
    receiveMessageFromServer();
//Step3
    Message sendline = {FIRST_CASE, "Wlazl kotek na plotek..."};
    g_unixWrapper.send(g_sockfd, &sendline, sizeof(sendline));
//Step4
    receiveMessageFromServer();
//Step5
    sendline.msgId = SECOND_CASE;
    strcpy(sendline.payload, "...i mruga...");
    g_unixWrapper.send(g_sockfd, &sendline, sizeof(sendline));
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

