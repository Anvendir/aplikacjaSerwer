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
#define SERWER_IP "127.0.0.1"

main()
{
    struct sockaddr_in serwer;
    int gniazdo;
    char bufor[ MAX_MSG_LEN ];

    bzero( & serwer, sizeof( serwer ) );
    bzero( bufor, sizeof( bufor ) );
    
    serwer.sin_family = AF_INET;
    serwer.sin_port = htons( SERWER_PORT );
    if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 )
    {
                perror( "inet_pton() ERROR" );
                        exit( - 1 );
                            }
    
    if(( gniazdo = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
                perror( "socket() ERROR" );
                        exit( - 1 );
                            }
    
    socklen_t len = sizeof( serwer );
    if( connect( gniazdo,( struct sockaddr * ) & serwer, len ) < 0 )
    {
                perror( "connect() ERROR" );
                        exit( - 1 );
                            }
    
    strcpy( bufor, "Wyslane z clienta" );
    if(( send( gniazdo, bufor, strlen( bufor ), 0 ) ) <= 0 )
    {
                perror( "send() ERROR" );
                        exit( - 1 );
                            }
    
    bzero( bufor, sizeof( bufor ) );
    if(( recv( gniazdo, bufor, sizeof( bufor ), 0 ) ) <= 0 )
    {
                perror( "recv() ERROR" );
                        exit( - 1 );
                            }
    printf( "|Wiadomosc z serwera|: %s \n", bufor );
    
    shutdown( gniazdo, SHUT_RDWR );
    return 0;
}
