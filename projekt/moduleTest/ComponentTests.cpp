#include "ComponentTests.hpp"
#include <fstream>

int main(int argc, char **argv)
{
    void (*testcasesList[])(int, char**) = {connectToServer,
                                            exchangeAFewSimpleMessagesWithServer,
                                            sendFileTransferRequestAndReceiveRequestedFile};

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
    Message l_sendline = {};
    l_sendline.msgId = FIRST_CASE;
    strcpy(l_sendline.payload, "Wlazl kotek na plotek...");

    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step4
    receiveMessageFromServer();
//Step5
    l_sendline.msgId = SECOND_CASE;
    strcpy(l_sendline.payload, "...i mruga...");
    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive welcome message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Check content of received file
 * Step6: Close connection
**************************************************************************/
void receiveMessageFromServer1(std::ofstream& p_outFile, long long& p_sumUp);
void sendFileTransferRequestAndReceiveRequestedFile(int p_argc, char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argc, p_argv);
//Step2
    receiveMessageFromServer();
//Step3
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    strcpy(l_sendline.payload, "./moduleTest/plikiPrzykladowe/duzyTekstowy.txt");

    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step4
    receiveMessageFromServer();
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;

    long long l_sumUp = 0;
    std::ofstream l_outFile("odebrany.txt");
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        std::cout << std::endl;
        std::cout << i << std::endl;
        receiveMessageFromServer1(l_outFile, l_sumUp);
        std::cout << "received bytes: " << l_sumUp << std::endl;
    }
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
    l_outFile.close();
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

