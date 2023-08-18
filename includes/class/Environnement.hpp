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
            std::string client_key = "fd0a43b230514b6c929d0895f5dacde6";
            std::string client_secret = "af63d053017d4db6a809edc7019f0627";
            std::string request_token_url = "https://accounts.spotify.com/api/token";
            std::string access_token_request = "grant_type=client_credentials";
            std::string access_token = "YOUR_ACCESS_TOKEN";
            std::string SPOTIFY_API_BASE_URL = "https://api.spotify.com/v1/";
            std::string authCode = "";
        private:
    };

#endif /* !ENV_HPP_ */

