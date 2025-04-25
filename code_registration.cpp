/**
 * @file code_registration.cpp
 * @brief Реализация регистрации нового пользователя, входа и проверок ввода.
 * @version 1.0
 * @date 2025
 */

#include "code_registration.h"
#include "chat_system.h"
#include "user.h"
#include "user_chat_list.h"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Проверка логина или пароля по длине и содержанию.
 *
 * @param inputData Введённая строка
 * @param contentLengthMin Минимальная длина
 * @param contentLengthMax Максимальная длина
 * @param isPassword true — если проверяется пароль, false — логин
 * @return true если строка валидна
 * @throws std::invalid_argument при нарушении условий
 */
bool checkNewDataInputForLimits(const std::string &inputData, std::size_t contentLengthMin,
                                std::size_t contentLengthMax, bool isPassword) {
  if (inputData.length() < contentLengthMin || inputData.length() > contentLengthMax) {
    throw std::invalid_argument("Некорректное количество символов.");
  }

  bool isCapital = false, isNumber = false;

  for (char ch : inputData) {
    if (!std::isalnum(ch)) {
      throw std::invalid_argument("Недопустимый символ: '" + std::string(1, ch) + "'");
    }
    if (std::isdigit(ch))
      isNumber = true;
    if (std::isupper(ch))
      isCapital = true;
  }

  if (isPassword) {
    if (!isCapital)
      throw std::invalid_argument("Требуется заглавная буква.");
    if (!isNumber)
      throw std::invalid_argument("Требуется цифра.");
  }

  return true;
}

/**
 * @brief Получает и валидирует ввод пользователя.
 *
 * @param prompt Текст подсказки
 * @param dataLengthMin Минимальная длина
 * @param dataLengthMax Максимальная длина
 * @param isPassword Является ли ввод паролем
 * @param userData Данные, к которым применяется проверка (используется для
 * сравнения или заполнения)
 * @param newUserData true — вводится новый пользователь
 * @param chatSystem Система чатов для валидации данных
 * @return std::string валидированная строка или "0" для выхода
 */
std::string inputDataValidation(const std::string &prompt, std::size_t dataLengthMin, std::size_t dataLengthMax,
                                bool isPassword, UserData userData, bool newUserData, const ChatSystem &chatSystem) {
  std::cout << prompt << std::endl;
  std::string inputData;

  while (true) {
    std::getline(std::cin, inputData);
    if (inputData.empty()) {
      std::cerr << "Вы ничего не ввели.\n";
      continue;
    }
    if (inputData == "0")
      return inputData;

    try {
      if (newUserData) {
        checkNewDataInputForLimits(inputData, dataLengthMin, dataLengthMax, isPassword);
      }
      return inputData;
    } catch (const std::exception &ex) {
      std::cerr << ex.what() << std::endl;
    }
  }
}

/**
 * @brief Поиск пользователя по логину.
 */
std::shared_ptr<User> findUserbyLogin(const std::string &userLogin, const ChatSystem &chatSystem) {
  const auto &users = chatSystem.getUsers();
  auto it = std::find_if(users.begin(), users.end(),
                         [&](const std::shared_ptr<User> &u) { return u->getLogin() == userLogin; });
  return (it != users.end()) ? *it : nullptr;
}

/**
 * @brief Проверяет наличие логина в системе.
 */
const std::shared_ptr<User> checkLoginExists(const std::string &login, const ChatSystem &chatSystem) {
  for (const auto &user : chatSystem.getUsers()) {
    if (user->getLogin() == login)
      return user;
  }
  return nullptr;
}

/**
 * @brief Проверка пароля для заданного логина.
 */
bool checkPasswordValidForUser(const UserData &userData, const ChatSystem &chatSystem) {
  auto user = findUserbyLogin(userData._login, chatSystem);
  return user && userData._password == user->getPassword();
}

/**
 * @brief Ввод и проверка логина пользователя.
 */
void inputNewLogin(UserData &userData, const ChatSystem &chatSystem) {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (true) {
    std::string newLogin = inputDataValidation("Введите логин (или 0 для выхода):", 5, 20, false, userData, true,
                                               chatSystem);

    if (newLogin == "0")
      return;
    if (checkLoginExists(newLogin, chatSystem)) {
      std::cerr << "Логин уже занят.\n";
      continue;
    }

    userData._login = newLogin;
    return;
  }
}

/**
 * @brief Ввод и проверка пароля пользователя.
 */
void inputNewPassword(UserData &userData, const ChatSystem &chatSystem) {
  std::string newPassword = inputDataValidation("Введите пароль (или 0 для выхода):", 5, 10, true, userData, true,
                                                chatSystem);
  if (newPassword != "0")
    userData._password = newPassword;
}

/**
 * @brief Ввод и проверка имени пользователя.
 */
void inputNewName(UserData &userData, const ChatSystem &chatSystem) {
  std::string newName = inputDataValidation("Введите имя (или 0 для выхода):", 3, 10, false, userData, true,
                                            chatSystem);
  if (newName != "0")
    userData._name = newName;
}

/**
 * @brief Регистрация нового пользователя.
 */
void userRegistration(ChatSystem &chatSystem) {
  std::cout << "Регистрация нового пользователя.\n";
  UserData userData;

  inputNewLogin(userData, chatSystem);
  if (userData._login.empty())
    return;

  inputNewPassword(userData, chatSystem);
  if (userData._password.empty())
    return;

  inputNewName(userData, chatSystem);
  if (userData._name.empty())
    return;

  auto newUser = std::make_shared<User>(userData._login, userData._name, userData._password);
  chatSystem.addUser(newUser);
  chatSystem.setActiveUser(newUser);
  newUser->showUserData();
  newUser->createChatList(std::make_shared<UserChatList>(newUser));
}

/**
 * @brief Авторизация пользователя в системе.
 *
 * @param chatSystem Система чатов
 * @return true если авторизация прошла успешно
 */
bool userLoginInsystem(ChatSystem &chatSystem) {
  UserData userData;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // логин
  while (true) {
    userData._login = inputDataValidation("Введите логин (или 0 для выхода):", 0, 0, false, userData, false,
                                          chatSystem);
    if (userData._login == "0")
      return false;

    if (!checkLoginExists(userData._login, chatSystem)) {
      std::cerr << "Такой логин не найден.\n";
      continue;
    }
    break;
  }
  // пароль
  userData._password = inputDataValidation("Введите пароль (или 0 для выхода):", 0, 0, true, userData, false,
                                           chatSystem);
  if (userData._password == "0")
    return false;

  if (!checkPasswordValidForUser(userData, chatSystem)) {
    std::cerr << "Неверный пароль.\n";
    return false;
  }

  auto user = findUserbyLogin(userData._login, chatSystem);
  chatSystem.setActiveUser(user);
  return true;
}
