/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** MyOauth
*/

#include "MyOauth.hpp"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void MyOauth::get_spotify_token ()
{
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return;
    }

    std::string url = "https://accounts.spotify.com/api/token";
    std::string postData = "grant_type=client_credentials&client_id=fd0a43b230514b6c929d0895f5dacde6&client_secret=af63d053017d4db6a809edc7019f0627";
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << response << std::endl;
        spotify_token = new Token (response);
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return;
}

void MyOauth::getCurrentSoungSpotify ()
{
    std::cout << "getCurrentSoungSpotify" << std::endl;
    CURL* curl;
    CURLcode res;

    // Initialisation de libcurl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return;
    }

    // URL de la requête GET pour les informations sur la musique en cours de lecture
    std::string url = "https://api.spotify.com/v1/me/player/currently-playing";

    // Ajoutez votre jeton d'accès à l'en-tête d'autorisation
    std::string accessToken = spotify_token->access_token;
    std::string authHeader = "Authorization: Bearer " + accessToken;

    // Liste d'en-têtes personnalisée
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, authHeader.c_str());

    // Configuration de la requête GET
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Spécification de la liste d'en-têtes personnalisée

    // Données de réponse
    std::string response;

    // Spécification de la fonction de rappel pour gérer les données de réponse
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Exécution de la requête GET
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        // Affichage de la réponse (qui contiendra les informations sur la musique en cours de lecture)
        std::cout << "Réponse du serveur : " << std::endl;
        std::cout << response << std::endl;
    }

    // Nettoyage
    curl_slist_free_all(headers); // Libération de la mémoire utilisée par la liste d'en-têtes
    curl_easy_cleanup(curl);

    return;
}

bool MyOauth::isAccessTokenValidSpotify ()
{
    CURL* curl;
    CURLcode res;
    bool isValid = false;

    // Initialisation de libcurl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return false;
    }

    // URL de la requête GET pour vérifier le jeton d'accès
    std::string url = "https://api.spotify.com/v1/me";

    // Ajoutez votre jeton d'accès à l'en-tête d'autorisation
    std::string authHeader = "Authorization: Bearer " + spotify_token->access_token;

    // Liste d'en-têtes personnalisée
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, authHeader.c_str());

    // Configuration de la requête GET
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Spécification de la liste d'en-têtes personnalisée

    // Données de réponse
    std::string response;

    // Spécification de la fonction de rappel pour gérer les données de réponse
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Exécution de la requête GET
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res == CURLE_OK) {
        // Si la requête a abouti sans erreur, le jeton est valide
        isValid = true;
    } else {
        // Affichage de l'erreur (pour le débogage, vous pouvez commenter cette ligne dans la version finale)
        std::cerr << "Erreur lors de la vérification du jeton : " << curl_easy_strerror(res) << std::endl;
    }

    // Nettoyage
    curl_slist_free_all(headers); // Libération de la mémoire utilisée par la liste d'en-têtes
    curl_easy_cleanup(curl);

    return isValid;
}

MyOauth::MyOauth (Environnement *envTmp)
{
    env = envTmp;
    get_spotify_token ();
}

MyOauth::~MyOauth ()
{
    delete (spotify_token);
}
