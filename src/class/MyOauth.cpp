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

std::string MyOauth::exchangeAuthorizationCodeForAccessToken (const std::string& authorizationCode)
{
    CURL* curl;
    CURLcode res;
    std::string accessToken;

    // Initialisation de libcurl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return "";
    }

    // URL de l'endpoint d'autorisation de Spotify
    std::string url = "https://accounts.spotify.com/api/token";

    // Données à envoyer dans la requête POST pour échanger le code d'autorisation contre le token
    std::string postData = "grant_type=authorization_code&code=" + authorizationCode + "&client_id=" + env->client_key + "&client_secret=" + env->client_secret + "&redirect_uri=http://localhost:8888/callback";

    // Configuration de la requête POST
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

    // Données de réponse
    std::string response;

    // Spécification de la fonction de rappel pour gérer les données de réponse
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, std::string* response) -> size_t {
        size_t totalSize = size * nmemb;
        response->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Exécution de la requête POST
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        // Traitement de la réponse JSON pour extraire le token d'accès
        // Notez que vous devrez inclure une bibliothèque JSON pour traiter la réponse JSON.
        // Vous pouvez utiliser une bibliothèque comme nlohmann/json pour cela.
        // Exemple : #include <nlohmann/json.hpp>
        //          nlohmann::json jsonResponse = nlohmann::json::parse(response);
        //          accessToken = jsonResponse["access_token"];
    }

    // Nettoyage
    curl_easy_cleanup(curl);

    return accessToken;
}

void MyOauth::get_spotify_token()
{
    CURL* curl;
    CURLcode res;

    // Initialisation de libcurl
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl." << std::endl;
        return;
    }

    // URL de l'endpoint d'authentification pour le "flux d'autorisation code d'autorisation"
    std::string authUrl = "https://accounts.spotify.com/authorize";

    // Paramètres requis pour l'authentification (à adapter en fonction de votre application)
    std::string clientId = env->client_key;
    std::string redirectUri = "http://localhost:8888/callback";
    std::string scope = "user-read-private user-read-email"; // Liste des autorisations requises, séparées par des espaces

    // Construire l'URL d'authentification avec les paramètres
    std::string authRequestUrl = authUrl + "?client_id=" + clientId + "&redirect_uri=" + redirectUri + "&response_type=code&scope=" + scope;

    // Afficher l'URL d'authentification pour que l'utilisateur puisse le visiter et donner son consentement
    std::cout << "Visitez cette URL dans votre navigateur pour donner votre consentement : " << std::endl;
    std::cout << authRequestUrl << std::endl;

    // Demander à l'utilisateur de copier le code de réponse après avoir donné son consentement
    while (env->authCode == "");

    // URL de l'endpoint pour obtenir le jeton d'accès
    std::string tokenUrl = "https://accounts.spotify.com/api/token";

    // Construire les données à envoyer dans la requête POST pour obtenir le jeton d'accès
    std::string postData = "grant_type=authorization_code&code=" + env->authCode + "&redirect_uri=" + redirectUri + "&client_id=" + clientId + "&client_secret=" + env->client_secret;

    // Liste d'en-têtes personnalisée pour spécifier le type de contenu de la requête
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    // Configuration de la requête POST pour obtenir le jeton d'accès
    curl_easy_setopt(curl, CURLOPT_URL, tokenUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;

    // Spécification de la fonction de rappel pour gérer les données de réponse
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Exécution de la requête POST pour obtenir le jeton d'accès
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        // Affichage de la réponse (qui contient le jeton d'accès)
        std::cout << "Réponse du serveur01: " << std::endl;
        std::cout << response << std::endl;

        // Analyser la réponse JSON pour extraire le jeton d'accès et d'autres informations nécessaires
        // (code à mettre en œuvre pour votre propre logique d'extraction des données)
    }

    // Nettoyage
    curl_slist_free_all(headers); // Libération de la mémoire utilisée par la liste d'en-têtes
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
