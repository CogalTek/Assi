/*
** EPITECH PROJECT, 2023
** Assi
** File description:
** Token
*/

#include "MyOauth.hpp"

Token::Token (std::string res)
{
    nlohmann::json responseJson = nlohmann::json::parse(res);
    access_token = responseJson["access_token"];
    token_type = responseJson["token_type"];
    expires_in = responseJson["expires_in"];
}

Token::~Token ()
{
}

