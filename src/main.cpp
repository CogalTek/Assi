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

    while (1) {
        if (!socket.ping()) {
            while (!socket.ping()) {
                sleep(1); // a revoir le sleep
                std::cout << "Timeout: " << i++ << std::endl;
            }
            i = 0;
        } else {
            std::cout << "Connecté" << std::endl;
        }
    }
}
