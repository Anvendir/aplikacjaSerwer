#include "ComponentTests.hpp"
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <boost/tokenizer.hpp>

int main(int p_argc, char** p_argv)
{
    std::map<std::string, void(*)(char**)> l_testcaseContainer =
{
  { "connectToServer", connectToServerTest },
  { "exchangeAFewSimpleMessagesWithServer", exchangeAFewSimpleMessagesWithServerTest },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_largeTextFile", sendFileTransferRequestAndReceiveRequestedFileTest_largeTextFile },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_smallTextFile", sendFileTransferRequestAndReceiveRequestedFileTest_smallTextFile },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_smallBinaryFile", sendFileTransferRequestAndReceiveRequestedFileTest_smallBinaryFile },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_largeBinaryFile", sendFileTransferRequestAndReceiveRequestedFileTest_largeBinaryFile },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_dicomFile", sendFileTransferRequestAndReceiveRequestedFileTest_dicomFile },
  { "sendFileTransferRequestAndReceiveRequestedFileTest_fileIsMultipleOf1024", sendFileTransferRequestAndReceiveRequestedFileTest_fileIsMultipleOf1024 },
  { "sendFileListRequestAndReceiveResponseWithProperFileListTest", sendFileListRequestAndReceiveResponseWithProperFileListTest },
  { "sendFileListRequestNextChoseOneFileAndRequestForIt", sendFileListRequestNextChoseOneFileAndRequestForIt },
  { "sendServerParseDicomFileReqAndReceivePositiveAnswer", sendServerParseDicomFileReqAndReceivePositiveAnswer },
  { "sendServerParseDicomFileReqAndReceiveNegativeAnswer", sendServerParseDicomFileReqAndReceiveNegativeAnswer },
  { "sendRequestParseOfSomeDicomFileThenAskForTextFileWithResultOfParsing", sendRequestParseOfSomeDicomFileThenAskForTextFileWithResultOfParsing },
  { "sendRequestParseOfSomeDicomFileThenAskForBinaryFileWithResultOfParsing", sendRequestParseOfSomeDicomFileThenAskForBinaryFileWithResultOfParsing }
};

    switch (p_argc)
    {
        case 2:
        {
            if(!strcmp("list", p_argv[1]))
            {
                listAllTestcases(l_testcaseContainer, p_argv);
            }
            else
            {
                runAllTestcases(l_testcaseContainer, p_argv);
            }
            break;
        }
        case 3:
        {
            runSingleTestcase(l_testcaseContainer, p_argv);
            break;
        }
        default:
        {
            std::cout << "Incorrect attempt of usage:\n" << getUsageMessage(p_argv) << std::endl;
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
    std::string l_samplePayload = "Wlazl kotek na plotek...";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_TEST_FIRST_REQ;
    l_sendline.bytesInPayload = strlen(l_samplePayload.c_str()) + 1;
    strcpy(l_sendline.payload, l_samplePayload.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_TEST_FIRST_RESP);
//Step5
    l_samplePayload = "...i mruga...";
    l_sendline.msgId = SERVER_TEST_SECOND_REQ;
    l_sendline.bytesInPayload = strlen(l_samplePayload.c_str()) + 1;
    strcpy(l_sendline.payload, l_samplePayload.c_str());
    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server (large text file)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_largeTextFile(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "duzyTekstowy.txt";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.txt";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server (small text file)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_smallTextFile(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "prostyPlik.txt";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.txt";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server (small binary jpg file)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_smallBinaryFile(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "malyJpeg.jpg";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.jpg";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server (large binary jpg file)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_largeBinaryFile(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "duzyJpeg.jpg";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.jpg";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server (DICOM file)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_dicomFile(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "plikDICOM.dcm";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.dcm";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_REQ to the server with text file
 *        which size is multiple of 1024 (in that case is 3 x 1024 -> 3072)
 * Step4: Receive SERVER_SEND_FILE_RESP message from server
 * Step5: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step6: Check if received and requested file are equal
 * Step7: Close connection
**************************************************************************/
void sendFileTransferRequestAndReceiveRequestedFileTest_fileIsMultipleOf1024(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sourceFileName = "plikORozmiarzeBrzegowym.txt";
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_sourceFileName;
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step5
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.txt";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step6
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_sourceFileName,
                                          l_outFileName);
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_LIST_REQ to the server
 * Step4: Receive SERVER_SEND_FILE_LIST_RESP message from server
 * Step5: Check if received list is equal to real list of file
 * Step6: Close connection
**************************************************************************/
void sendFileListRequestAndReceiveResponseWithProperFileListTest(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "File list request.";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_LIST_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_LIST_RESP);
//Step5
    //checkIfReceivedAndActualFileListMatch();
//Step6
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_SEND_FILE_LIST_REQ to the server
 * Step4: Receive SERVER_SEND_FILE_LIST_RESP message from server
 * Step5: Chose one file and send message SERVER_SEND_FILE_REQ
 * Step6: Receive SERVER_SEND_FILE_RESP message from server
 * Step7: Receive number of CLIENT_SEND_FILE_IND messages as defined in
 *        numOfMsgInFileTransfer field of SERVER_SEND_FILE_RESP
 * Step8: Check if received and requested file are equal
 * Step9: Close connection
**************************************************************************/
void sendFileListRequestNextChoseOneFileAndRequestForIt(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "File list request.";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_LIST_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_SEND_FILE_LIST_RESP);
//Step5
    std::string l_receivedFileListInOnePiece;
    l_receivedFileListInOnePiece.append(g_receivedMessage.payload, g_receivedMessage.bytesInPayload);
    std::vector<std::string> l_fileList = splitString(l_receivedFileListInOnePiece, "\n");

    l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    std::string l_sourceFilePath = "./moduleTest/plikiPrzykladowe/" + l_fileList[0];
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());
    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step6
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step7
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebrany.jpg";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step8
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/" + l_fileList[0],
                                          l_outFileName);
//Step9
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_PARSE_DICOM_FILE_REQ to the server
 * Step4: Receive message SERVER_PARSE_DICOM_FILE_RESP from server with positive answer
 * Step5: Close connection
**************************************************************************/
void sendServerParseDicomFileReqAndReceivePositiveAnswer(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "./moduleTest/plikiPrzykladowe/CT0001.dcm";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_PARSE_DICOM_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_PARSE_DICOM_FILE_RESP);
    checkIfPossitiveMessageIsReceived(g_receivedMessage.payload);
//Step5
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_PARSE_DICOM_FILE_REQ to the server
 * Step4: Receive message SERVER_PARSE_DICOM_FILE_RESP from server with negative answer
 * Step5: Close connection
**************************************************************************/
void sendServerParseDicomFileReqAndReceiveNegativeAnswer(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "./moduleTest/plikiPrzykladowe/brakPliku";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_PARSE_DICOM_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_PARSE_DICOM_FILE_RESP);
    checkIfNegativeMessageIsReceived(g_receivedMessage.payload);
//Step5
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_PARSE_DICOM_FILE_REQ to the server
 * Step4: Receive message SERVER_PARSE_DICOM_FILE_RESP from server with positive answer with file list
 * Step5: Request of text file with result of parsing
 * Step6: Recieve requested file
 * Step7: Close connection
**************************************************************************/
void sendRequestParseOfSomeDicomFileThenAskForTextFileWithResultOfParsing(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "./moduleTest/plikiPrzykladowe/CT0001.dcm";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_PARSE_DICOM_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_PARSE_DICOM_FILE_RESP);
    checkIfPossitiveMessageIsReceived(g_receivedMessage.payload);
    std::string l_temp = g_receivedMessage.payload;
    std::string l_textFile = l_temp.substr(0, l_temp.find(" "));

//Step5
    l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    std::string l_sourceFilePath = l_textFile;
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());
    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step6
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step6.1
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebranyRezultatParsowania.txt";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step7
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

/**************************************************************************
 * Test scenario:
 * Step1: Setup connection with server with address 192.168.254.1
 * Step2: Receive CLIENT_WELCOME_MSG_IND message from server
 * Step3: Send message SERVER_PARSE_DICOM_FILE_REQ to the server
 * Step4: Receive message SERVER_PARSE_DICOM_FILE_RESP from server with positive answer with file list
 * Step5: Request of png file with result of parsing
 * Step6: Recieve requested file
 * Step7: Check if file is correct
 * Step8: Close connection
**************************************************************************/
void sendRequestParseOfSomeDicomFileThenAskForBinaryFileWithResultOfParsing(char** p_argv)
{
    std::cout << "Testcase " << __FUNCTION__ << " started." << std::endl;
//Step1
    initializeConnection(p_argv);
//Step2
    receiveMessageFromServer(CLIENT_WELCOME_MSG_IND);
//Step3
    std::string l_sampleMsg = "./moduleTest/plikiPrzykladowe/CT0001.dcm";
    Message l_sendline = {};
    l_sendline.msgId = SERVER_PARSE_DICOM_FILE_REQ;
    l_sendline.bytesInPayload = strlen(l_sampleMsg.c_str()) + 1;
    strcpy(l_sendline.payload, l_sampleMsg.c_str());

    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step4
    receiveMessageFromServer(SERVER_PARSE_DICOM_FILE_RESP);
    checkIfPossitiveMessageIsReceived(g_receivedMessage.payload);
    std::string l_temp = g_receivedMessage.payload;

    boost::char_separator<char> l_separator(" ");
    boost::tokenizer<boost::char_separator<char>> l_resultFilePathsContainer(l_temp, l_separator);
    auto l_it = l_resultFilePathsContainer.begin();
    std::string l_binaryFile = *(++l_it);

//Step5
    l_sendline = {};
    l_sendline.msgId = SERVER_SEND_FILE_REQ;
    std::string l_sourceFilePath = l_binaryFile;
    l_sendline.bytesInPayload = strlen(l_sourceFilePath.c_str()) + 1;
    strcpy(l_sendline.payload, l_sourceFilePath.c_str());
    g_unixWrapper.send(g_sockfd, &l_sendline);
//Step6
    receiveMessageFromServer(SERVER_SEND_FILE_RESP);
    int l_numberOfMessagesToCatch = g_receivedMessage.numOfMsgInFileTransfer;
    std::cout << "Number of messages to catch: " << l_numberOfMessagesToCatch << std::endl;
//Step6.1
    long long l_sumOfReceivedBytes = 0;
    std::string l_outFileName = "odebranyRezultatParsowania.png";
    std::ofstream l_outFile(l_outFileName);
    for (int i = 0; i < l_numberOfMessagesToCatch; i++)
    {
        receiveMessageClientSendFileIndFromServer(l_outFile, l_sumOfReceivedBytes);
    }
    std::cout << "Amount of received bytes: " << l_sumOfReceivedBytes << std::endl;
    l_outFile.close();
//Step7
    checkIfRequestedAndReceivedFilesMatch("./plikiPrzykladowe/CT0001.dcm.png", l_outFileName);
//Step8
    g_unixWrapper.close(g_sockfd);
    std::cout << "Testcase " << __FUNCTION__ << " finished successfully." << std::endl;
}

