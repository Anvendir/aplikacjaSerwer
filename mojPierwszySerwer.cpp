#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    std::cout << "Hello World" << std::endl;

    int pierwszySocket;
    sockaddr_in mojAdres;
    pierwszySocket = socket(PF_INET, SOCK_STREAM, 0);

    mojAdres.sin_family = PF_INET;
    mojAdres.sin_port = htons(3400);
    mojAdres.sin_addr.s_addr = inet_addr("192.168.254.1");
    memset(&(mojAdres.sin_addr), '\0', 8);

    std::cout << PF_INET << std::endl;
    std::cout << ntohs(mojAdres.sin_port) << std::endl;
    std::cout << mojAdres.sin_addr.s_addr << std::endl;
    std::cout << pierwszySocket << std::endl;
 
    bind(pierwszySocket, reinterpret_cast<sockaddr *>(&mojAdres), sizeof(sockaddr));
    listen(pierwszySocket, 5);
    sockaddr_in adresNadawcy;
    int x = sizeof(sockaddr_in);
    int drugiSocket = accept(pierwszySocket, reinterpret_cast<sockaddr *>(&adresNadawcy), reinterpret_cast<socklen_t*>(&x));

    std::cout << inet_ntoa(adresNadawcy.sin_addr) << std::endl;

    return 0;
}
