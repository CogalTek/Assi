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
            std::cout << "Timeout: " << i++ << std::endl;
        } else {
            std::cout << "Connecté" << std::endl;
            i = 0;
        }
    }
}
