/// @brief регистрация нового пользователя

#pragma once
#include <string>

/// @brief проверка ввода текста
bool checkInputNewLoginPassword(const std::string &inputData,
                                std::size_t contentLengthMin,
                                std::size_t contentLengthMax, bool password);

void inputNewLogin(); /// @brief ввод нового логина

void inputNewPassword(); /// @brief ввод нового пароля

void userRegistration(); /// @brief регистрация нового пользователя