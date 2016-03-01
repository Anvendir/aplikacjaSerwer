#include "Dispatcher.hpp"
#include "UnixWrappers.hpp"
#include "CommonTypes.h"
#include <iostream>

Dispatcher::Dispatcher(std::shared_ptr<IUnixWrappers> p_unixWrapper)
    : m_unixWrapper(p_unixWrapper)
{

}

void Dispatcher::dispatch(int p_clientSocket, const Message p_receivedMsg) const
{
    switch(p_receivedMsg.msgId)
    {
        case 1:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case 1: , otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;

            Message l_sendline = {1, "Odpowiedz"};
            m_unixWrapper->send(p_clientSocket, &l_sendline, sizeof(l_sendline));
            break;
        }
        case 2:
        {
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Case 2: , otrzymana wiadomosc to - " << p_receivedMsg.payload
                      << std::endl;
            break;
        }
        default:
            std::cout << "PID: " << m_unixWrapper->getPid() << " | "
                      << "Nieznany identyfikator" << std::endl;
    }
}
