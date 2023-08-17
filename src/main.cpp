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
    std::cout << "Connecté" << std::endl;
    std::cout << "debug adresse abc : " << &socket << std::endl;
    std::thread monThread([socketPtr]() {
        socketPtr->thread_server ();
    });
    MyOauth temp (&env);
    std::cout << "debug quit MyOauth" << std::endl;
    // while (1);
    // while (1) {
    //     std::cout << "debug Entre dans la boucle" << std::endl;
    //     if (temp.isAccessTokenValidSpotify()) {
    //         temp.getCurrentSoungSpotify();
    //     } else {
    //         std::cout << "Le jeton d'accès n'est pas valide." << std::endl;
    //     }
    // }
    monThread.join();
}
