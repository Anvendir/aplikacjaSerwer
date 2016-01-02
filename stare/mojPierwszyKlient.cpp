#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char * argv[])
{
    std::cout << "Hello World" << std::endl;

    int pierwszySocket;
    sockaddr_in adresDocelowy;
    pierwszySocket = socket(PF_INET, SOCK_STREAM, 0);

    hostent * he = gethostbyname( argv[ 1 ] );
    adresDocelowy.sin_family = PF_INET; // host byte order 
    adresDocelowy.sin_port = htons( 3401 ); // short, network byte order 
    adresDocelowy.sin_addr = *(( struct in_addr * ) he->h_addr );
    memset( &( adresDocelowy.sin_zero ), '\0', 8 ); // wyzeruj resztę struktury
   // adresDocelowy.sin_family = PF_INET;
   // adresDocelowy.sin_port = htons(3490);
   // adresDocelowy.sin_addr.s_addr  = inet_addr("192.168.255.1");
   // memset(&(adresDocelowy.sin_addr), '\0', 8);

    int i = 5;
    i =  connect(pierwszySocket,
                 reinterpret_cast<sockaddr *>(&adresDocelowy),
                 sizeof(sockaddr));
    std::cout << i << std::endl;

    std::string wiadomosc = "Powitanie!";
    int wyslane = send(pierwszySocket, &wiadomosc, sizeof(wiadomosc), 0);
    std::cout << wyslane << std::endl;    
    return 0;
}
