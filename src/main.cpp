/*
** EPITECH PROJECT, 2023
** Projet
** File description:
** main
*/

#include "my.hpp"
#include <unistd.h>

int main (void)
{
    Socket socket;
    Socket *socketPtr = &socket;
    Environnement env;
    socket.setEnv(&env);
    int i = 0;

    while (!socket.ping())
        std::cout << "Timeout: " << i++ << std::endl;
    std::thread monThread([socketPtr]() {
        socketPtr->thread_server ();
    });
    MyOauth temp (&env);
    while (1) {
        temp.getCurrentSoungSpotify();
        sleep(10);
    }
    monThread.join();
}
