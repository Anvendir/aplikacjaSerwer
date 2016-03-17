#include "ComponentTests.hpp"
#include <fstream>
#include <string>
#include <map>

int main(int argc, char **argv)
{
    std::map<std::string, void(*)(char**)> l_testcaseContainer
        = { {"connectToServer", connectToServerTest},
            {"exchangeAFewSimpleMessagesWithServer", exchangeAFewSimpleMessagesWithServerTest},
            {"sendFileTransferRequestAndReceiveRequestedFile", sendFileTransferRequestAndReceiveRequestedFileTest}
          };

    switch (argc)
    {
        case 3:
        {
            void(*l_testcase)(char**) = l_testcaseContainer.find(argv[2])->second;
            (l_testcase)(argv);

            break;
        }
        case 2:
        {
            for (auto l_it = l_testcaseContainer.begin(); l_it != l_testcaseContainer.end(); ++l_it)
            {
                void(*l_testcase)(char**) = *l_it->second;
                (l_testcase)(argv);
            }

            break;
        }
        default:
        {
		    g_errorHandler.handleHardError("usage: tcpcli <IPaddress>");
        }
    }

	exit(0);
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Close connection
**************************************************************************/

void connectToServerTest(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_TEST_FIRST_REQ to the server
 * Step4: Receive message SERVER_TEST_FIRST_RESP from server
 * Step5: Send message SERVER_TEST_SECOND_REQ to the server
 * Step6: Close connection
**************************************************************************/

void exchangeAFewSimpleMessagesWithServerTest(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    Message l_sendline = {};
    l_sendline.msgId = SERVER_TEST_FIRST_REQ;
    strcpy(l_sendline.payload, "Wlazl kotek na plotek...");

    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step4
    receiveMessageFromServer(SERVER_TEST_FIRST_RESP);
//Step5
    l_sendline.msgId = SERVER_TEST_SECOND_REQ;
    strcpy(l_sendline.payload, "...i mruga...");
    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check content of received file
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    char l_sourceFilePath[] = "./moduleTest/plikiPrzykladowe/duzyTekstowy.txt";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    strcpy(l_sendline.payload, l_sourceFilePath);

    g_unixWrapper.send(g_sockfd, &l_sendline, sizeof(l_sendline));
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::ofstream l_outFile("odebrany.txt");
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

