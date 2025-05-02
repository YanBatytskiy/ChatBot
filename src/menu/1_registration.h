/**
 * @file code_registration.h
 * @brief Объявления функций для регистрации и входа пользователя, а также валидации ввода.
 *
 * Этот файл содержит интерфейсы для работы с данными пользователя,
 * включая регистрацию, проверку логина и пароля, а также вспомогательные функции
 * взаимодействия с системой чатов ChatBot.
 */

#pragma once
#include "system/chat_system.h"
#include <cstddef>
#include <memory>
#include <string>

/**
 * @brief Структура для хранения данных пользователя, вводимых при регистрации или входе.
 */
struct UserData {
  std::string _login;    ///< Логин пользователя
  std::string _password; ///< Пароль пользователя
  std::string _name;     ///< Отображаемое имя пользователя
};

/**
 * @brief Проверка введённого логина или пароля на соответствие заданным ограничениям.
 *
 * @param inputData Введённая строка
 * @param contentLengthMin Минимальная допустимая длина
 * @param contentLengthMax Максимальная допустимая длина
 * @param isPassword Является ли это проверка пароля (true) или логина (false)
 * @return true если строка валидна
 * @throws std::invalid_argument при несоответствии требованиям
 */
bool checkNewDataInputForLimits(const std::string &inputData, std::size_t contentLengthMin,
                                std::size_t contentLengthMax, bool isPassword);

/**
 * @brief Проверка пользовательского ввода с повторными попытками.
 *
 * Функция отображает подсказку, получает ввод от пользователя, валидирует его
 * и возвращает проверенное значение. Может использовать данные пользователя
 * и систему чатов для дополнительной логики проверки.
 *
 * @param prompt Сообщение пользователю
 * @param dataLengthMin Минимальная длина вводимого значения
 * @param dataLengthMax Максимальная длина вводимого значения
 * @param isPassword true — если это пароль
 * @param dataForValidation Структура для хранения/сравнения вводимых данных
 * @param newUserData true — если создается новый пользователь
 * @param chatSystem Ссылка на глобальную систему чатов
 * @return std::string Проверенное значение
 */
std::string inputDataValidation(const std::string &prompt, std::size_t dataLengthMin, std::size_t dataLengthMax,
                                bool isPassword, UserData dataForValidation, bool newUserData,
                                const ChatSystem &chatSystem);

/**
 * @brief Поиск пользователя по логину в системе.
 *
 * @param userLogin Логин для поиска
 * @param chatSystem Ссылка на систему чатов
 * @return std::shared_ptr<User> Указатель на найденного пользователя или nullptr
 */
std::shared_ptr<User> findUserbyLogin(const std::string &userLogin, const ChatSystem &chatSystem);

/**
 * @brief Проверяет, существует ли пользователь с заданным логином.
 *
 * @param login Проверяемый логин
 * @param chatSystem Система чатов
 * @return std::shared_ptr<User> Указатель на пользователя, если найден
 */
const std::shared_ptr<User> checkLoginExists(const std::string &login, const ChatSystem &chatSystem);

/**
 * @brief Проверяет, соответствует ли пароль пользователю в системе.
 *
 * @param userData Структура с логином и паролем
 * @param chatSystem Система чатов
 * @return true если пароль корректен
 */
bool checkPasswordValidForUser(const UserData &userData, const ChatSystem &chatSystem);

/**
 * @brief Запрашивает и валидирует новый логин.
 *
 * @param userData Структура, в которую сохраняется логин
 * @param chatSystem Система чатов для проверки уникальности
 */
void inputNewLogin(UserData &userData, const ChatSystem &chatSystem);

/**
 * @brief Запрашивает и валидирует новый пароль.
 *
 * @param userData Структура, в которую сохраняется пароль
 * @param chatSystem Система чатов
 */
void inputNewPassword(UserData &userData, const ChatSystem &chatSystem);

/**
 * @brief Запрашивает и валидирует новое имя пользователя.
 *
 * @param userData Структура, в которую сохраняется имя
 * @param chatSystem Система чатов
 */
void inputNewName(UserData &userData, const ChatSystem &chatSystem);

/**
 * @brief Выполняет полную процедуру регистрации нового пользователя.
 *
 * Включает ввод и проверку логина, пароля и имени.
 *
 * @param chatSystem Ссылка на глобальную систему чатов
 */
void userRegistration(ChatSystem &chatSystem);

/**
 * @brief Авторизация пользователя в системе.
 *
 * @param chatSystem Система чатов
 * @return true если авторизация успешна, false — при ошибке входа
 */
bool userLoginInsystem(ChatSystem &chatSystem);
