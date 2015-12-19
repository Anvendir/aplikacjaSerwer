#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_MSG_LEN 4096
#define SERWER_PORT 8888
#define SERWER_IP "192.168.254.1"
#define CLIENT_PORT 4244
#define CLIENT_IP "192.168.254.20"

main()
{
    struct sockaddr_in serwer, client;
    int gniazdo;

    char bufor[MAX_MSG_LEN];

    memset(&serwer, 0, sizeof(serwer));
    memset(&client, 0, sizeof(client));
    memset(bufor, 0, sizeof(bufor));
    
    serwer.sin_family = AF_INET;
    serwer.sin_port = htons(SERWER_PORT);

    if (inet_pton(AF_INET, SERWER_IP, &serwer.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(-1);
    }
    
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    if (inet_pton(AF_INET, CLIENT_IP, &client.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(-1);
    }

    if ((gniazdo = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() ERROR");
        exit(-1);
    }

    socklen_t len = sizeof(serwer);
    if (bind(gniazdo, (struct sockaddr *) &client, len) < 0)
    {
        perror("bind() ERROR");
        exit(-1);
    }

    if (connect(gniazdo, (struct sockaddr*) &serwer, len) < 0)
    {
        perror("connect() ERROR");
        exit(-1);
    }
   
    strcpy(bufor, "Wyslane z clienta");
    if ((send(gniazdo, bufor, strlen(bufor), 0)) <= 0)
    {
        perror("send() ERROR");
        exit(-1);
    }
    
    memset(bufor, 0, sizeof(bufor));
    if ((recv(gniazdo, bufor, sizeof(bufor), 0)) <= 0)
    {
        perror("recv() ERROR");
        exit(-1);
    }
    printf("|Wiadomosc z serwera|: %s \n", bufor);
    
    shutdown(gniazdo, SHUT_RDWR);
    return 0;
}
