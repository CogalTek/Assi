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

bool Socket::ping()
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

void Socket::handleClient(int clientSocket)
{
    // Buffer pour stocker la requête HTTP
    char buffer[1024];
    std::string request;

    // Lire la requête HTTP depuis le client
    ssize_t bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        request += std::string(buffer, bytesRead);
        if (request.find("\r\n\r\n") != std::string::npos) {
            // Fin de la requête HTTP
            break;
        }
    }

    // Analyser la requête HTTP pour extraire le code d'autorisation
    // Code à mettre en œuvre pour extraire le code d'autorisation de l'URL de la "redirect URI"

    // Envoyer une réponse HTTP avec un message de confirmation au client
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    response += "<html><body><h1>Authentification réussie ! Vous pouvez maintenant fermer cette fenêtre.</h1></body></html>";
    send(clientSocket, response.c_str(), response.size(), 0);

    // Fermer la connexion avec le client
    close(clientSocket);
}

void Socket::thread_server ()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Créer le socket du serveur
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return;
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Lier le socket du serveur à l'adresse
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Erreur lors de la liaison du socket à l'adresse." << std::endl;
        close(serverSocket);
        return;
    }

    // Mettre le socket en écoute
    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Erreur lors de la mise en écoute du socket." << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Serveur en attente de connexions sur le port " << PORT << "..." << std::endl;

    while (true) {
        // Accepter les connexions entrantes
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Erreur lors de l'acceptation de la connexion entrante." << std::endl;
            continue;
        }

        // Gérer la connexion avec le client dans un thread séparé
        handleClient(clientSocket);
    }

    // Fermer le socket du serveur
    close(serverSocket);

    return;
}
