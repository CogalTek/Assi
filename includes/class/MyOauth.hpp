/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** MyOauth
*/

#ifndef MY_OAUTH_HPP_
#define MY_OAUTH_HPP_

    #include <iostream>
    #include <oauth.h>
    #include "Environnement.hpp"

    class MyOauth {
        public:
            MyOauth (Environnement *envTmp);
            ~MyOauth ();
        private:
            Environnement *env;
            std::string auth_header;
    };

#endif /* !MY_OAUTH_HPP_ */
