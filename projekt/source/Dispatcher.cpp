#include "Dispatcher.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <iostream>

//do usuniecia po owrapowaniu getpid
#include <sys/types.h>
#include <unistd.h>

Dispatcher::Dispatcher(std::shared_ptr<IErrorHandler> p_errorHandler) :
        m_unixWrapper(std::make_unique<UnixWrappers>(p_errorHandler))
{

}

void Dispatcher::dispatch(int p_clientSocket, const Message p_receivedMsg) const
{
    switch(p_receivedMsg.msgId)
    {
        case 1:
        {
            std::cout << "PID: " << getpid() << " | "
                      << "Case 1: , otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;

            Message l_sendline = {1, "Odpowiedz"};
            m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(l_sendline));
            break;
        }
        case 2:
        {
            std::cout << "PID: " << getpid() << " | "
                      << "Case 2: , otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;
            break;
        }
        default:
            std::cout << "PID: " << getpid() << " | "
                      << "Nieznany identyfikator" << std::endl;
    }
}
