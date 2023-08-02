/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** Socket
*/

#include "socket.hpp"
#include <curl/curl.h>

Socket::Socket()
{
}

Socket::~Socket()
{
}

bool Socket::ping ()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        // Utiliser CURLOPT_NOBODY pour effectuer une requête HEAD (sans corps de réponse)
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
            return true;

        curl_easy_cleanup(curl);
        return false;
    }
    return false;
}

void Socket::thread_server ()
{
    // Créer une instance du serveur web
    httplib::Server server;

    // Route pour gérer la réponse de redirection de Spotify
    server.Get("/callback", [&](const httplib::Request& req, httplib::Response& res) {
        // Extraire le code d'autorisation de l'URL de la requête
        std::string authorizationCode = req.get_param_value("code");

        // Afficher le code d'autorisation dans le terminal (à des fins de débogage)
        std::cout << "Code d'autorisation : " << authorizationCode << std::endl;

        // Stocker le code d'autorisation dans l'environnement
        env->authCode = authorizationCode;

        // Envoyer une réponse HTTP avec un message de confirmation au client
        res.set_content("Authentification réussie ! Vous pouvez maintenant fermer cette fenêtre.", "text/html");

        // Arrêter le serveur web après avoir reçu le code d'autorisation
        server.stop();
    });

    // Démarrer le serveur web sur le port 8888 (ou tout autre port de votre choix)
    server.listen("localhost", 8888);
}

