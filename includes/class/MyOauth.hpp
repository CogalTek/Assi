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
    #include <string>
    #include <curl/curl.h>
    #include <nlohmann/json.hpp>
    #include <cstdlib>

    class Token {
        public:
            Token (std::string res);
            ~Token ();
            std::string access_token = "";
            std::string token_type = "";
            std::size_t expires_in = 0;
    };

    class MyOauth {
        public:
            MyOauth (Environnement *envTmp);
            ~MyOauth ();
            void getCurrentSoungSpotify ();
            bool isAccessTokenValidSpotify ();
        private:
            std::string exchangeAuthorizationCodeForAccessToken (const std::string& authorizationCode);
            Environnement *env;
            std::string auth_header;
            void get_spotify_token ();
            Token *spotify_token;
            void openLinkInBrowser(const std::string link);
    };

#endif /* !MY_OAUTH_HPP_ */
