/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

    #include <iostream>
    #include <oauth.h>
    #include <string>
    #include <cstring>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

    class Socket {
        public:
            Socket ();
            ~Socket ();
            void thread_server ();
            bool ping ();
        private:
            void handleClient (int clientSocket);
            static const int PORT = 8888;
    };

#endif /* !SOCKET_HPP_ */
