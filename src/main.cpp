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
    Environnement env;
    int i = 0;

    while (!socket.ping()) {
        std::cout << "Timeout: " << i++ << std::endl;
    }
    std::cout << "Connecté" << std::endl;
    MyOauth temp (&env);
    while (1) {
        // while (!socket.ping())
        //     std::cout << "Timeout: " << i++ << std::endl;
        // i = 0;
        if (temp.isAccessTokenValidSpotify()) {
            temp.getCurrentSoungSpotify();
        } else {
            std::cout << "Le jeton d'accès n'est pas valide." << std::endl;
        }

        // temp.getCurrentSoungSpotify();
    }
}
