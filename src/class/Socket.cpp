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







