/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** env
*/

#ifndef ENV_HPP_
#define ENV_HPP_

    #include <iostream>

    class Environnement {
        public:
            Environnement ();
            ~Environnement ();
            std::string client_key = "YOUR_CLIENT_KEY";
            std::string client_secret = "YOUR_CLIENT_SECRET";
            std::string request_token_url = "https://accounts.spotify.com/api/token";
            std::string access_token_request = "grant_type=client_credentials";
            std::string access_token = "YOUR_ACCESS_TOKEN";
            std::string SPOTIFY_API_BASE_URL = "https://api.spotify.com/v1/";
        private:
    };

#endif /* !ENV_HPP_ */

