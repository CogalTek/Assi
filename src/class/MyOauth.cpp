/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** MyOauth
*/

#include "MyOauth.hpp"
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

MyOauth::MyOauth (Environnement *envTmp)
{
    env = envTmp;
    CURL* curl;
    CURLcode res;

    // Initialisation de libcurl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return;
    }

    // URL de la requête POST
    std::string url = "https://accounts.spotify.com/api/token";

    // Données à envoyer dans la requête POST (vous pouvez modifier cela en fonction de vos besoins)
    std::string postData = "grant_type=client_credentials&client_id=fd0a43b230514b6c929d0895f5dacde6&client_secret=af63d053017d4db6a809edc7019f0627";

    // Liste d'en-têtes personnalisée
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    // Configuration de la requête POST
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Spécification de la liste d'en-têtes personnalisée

    // Données de réponse
    std::string response;

    // Spécification de la fonction de rappel pour gérer les données de réponse
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Exécution de la requête POST
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        // Affichage de la réponse
        std::cout << "Réponse du serveur : " << std::endl;
        std::cout << response << std::endl;
    }

    // Nettoyage
    curl_slist_free_all(headers); // Libération de la mémoire utilisée par la liste d'en-têtes
    curl_easy_cleanup(curl);

    return;
}

MyOauth::~MyOauth ()
{
}
