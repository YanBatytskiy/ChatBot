/**
 * @file code_registration.h
 * @brief Объявления функций для регистрации пользователя и валидации ввода.
 *
 * Содержит набор функций, необходимых для получения и проверки логина и пароля
 * нового пользователя в текстовом интерфейсе ChatBot.
 */

#pragma once
#include "chat_system.h"
#include <cstddef>
#include <string>

/**
 * @brief Проверка введённого логина или пароля на соответствие правилам.
 *
 * Функция проверяет длину строки, допустимые символы (только латиница и цифры),
 * а также, если ввод — это пароль, наличие хотя бы одной цифры и заглавной
 * буквы.
 *
 * @param inputData Введённая пользователем строка
 * @param contentLengthMin Минимально допустимая длина строки
 * @param contentLengthMax Максимально допустимая длина строки
 * @param isPassword true — если проверяется пароль; false — если логин
 * @return true если строка корректна
 * @throws std::invalid_argument если ввод не соответствует требованиям
 */

struct UserData {
  std::string _login;
  std::string _password;
  std::string _name;
};

bool checkInputNewData(const std::string &inputData,
                       std::size_t contentLengthMin,
                       std::size_t contentLengthMax, bool isPassword);

/**
 * @brief Проверка ввода с повторными попытками до получения корректного
 * результата.
 *
 * Функция запрашивает ввод строки с клавиатуры, проверяет её и при ошибке
 * выводит соответствующее сообщение и предлагает ввести повторно.
 *
 * @param prompt Сообщение для пользователя
 * @param passwordLengthMin Минимальная длина строки
 * @param passwordLengthMax Максимальная длина строки
 * @param isPassword Флаг: true — проверка пароля, false — логина
 */
void inputDataValidation(const std::string &prompt, std::size_t dataLengthMin,
                         std::size_t dataLengthMax, bool isPassword,
                         std::string &userData, bool newUserData,
                         const ChatSystem &chatSystem);

bool checkIsUserDataInSystem(const std::string &login,
                          const ChatSystem &chatSystem, bool password);

/**
 * @brief Запрашивает у пользователя новый логин и проверяет его.
 */
void inputNewLogin(std::string &login, const ChatSystem &chatSystem);

/**
 * @brief Запрашивает у пользователя новый пароль и проверяет его.
 */
void inputNewPassword(std::string &password, const ChatSystem &chatSystem);

/**
 * @brief Запрашивает у пользователя нновое имя проверяет его.
 */
void inputNewName(std::string &name, const ChatSystem &chatSystem);

/**
 * @brief Основная функция регистрации нового пользователя.
 *
 * Вызывает процедуры ввода логина и пароля с последующей валидацией.
 */
void userRegistration(ChatSystem &chatSystem);

bool userLoginInsystem(ChatSystem &chatSystem);
