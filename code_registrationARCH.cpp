/**
 * @file code_registration.cpp
 * @brief Реализация регистрации нового пользователя и проверок ввода.
 * @version 1.0
 * @date 2025
 */

#include "code_registration.h"
#include "chat_system.h"
#include "user.h"
#include "user_chat_list.h"
#include <cctype>
#include <cstddef>
#include <cstring>
#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

/**
 * @brief Проверка корректности ввода логина или пароля.
 *
 * Проверяет длину строки, допустимые символы, наличие цифр и заглавных букв для
 * пароля.
 *
 * @param inputData Введённая пользователем строка
 * @param passwordLengthMin Минимальная допустимая длина
 * @param passwordLengthMax Максимальная допустимая длина
 * @param isPassword Флаг: true — проверка пароля, false — проверка логина
 * @return true если строка валидна
 * @throws std::invalid_argument при нарушении правил валидации
 */
bool checkInputNewData(const std::string &inputData,
                       std::size_t contentLengthMin,
                       std::size_t contentLengthMax, bool isPassword) {

  if (inputData.length() < contentLengthMin ||
      inputData.length() > contentLengthMax) {
    throw std::invalid_argument(
        "Некорректное количество символов. Попробуйте еще раз.");
  }

  bool isCapital = false;
  bool isNumber = false;
  //   char wrongChar;

  for (const char &ch : inputData) {
    if (!std::isalnum(ch)) {
      //   wrongChar = ch;
      throw std::invalid_argument("Должны быть только буквы и цифры. Символ '" +
                                  std::string(1, ch) + "'");
    }
    if (std::isdigit(ch))
      isNumber = true;
    if (std::isupper(ch))
      isCapital = true;
  }

  if (!isCapital && isPassword) {
    throw std::invalid_argument(
        "Должна быть минимум одна заглавная буква. Попробуйте еще раз:");
  }
  if (!isNumber && isPassword) {
    throw std::invalid_argument(
        "Должна быть минимум одна цифра. Попробуйте еще раз:");
  }

  return true;
}

/**
 * @brief Проверка пользовательского ввода с повторным запросом до успешного
 * ввода.
 *
 * Выводит сообщение, получает строку с клавиатуры и валидирует её.
 *
 * @param prompt Сообщение пользователю
 * @param passwordLengthMin Минимальная длина
 * @param passwordLengthMax Максимальная длина
 * @param isPassword Является ли это вводом пароля
 */
void inputDataValidation(const std::string &prompt,
                         std::size_t passwordLengthMin,
                         std::size_t passwordLengthMax, bool isPassword,
                         std::string &userData, bool newUserData,
                         const ChatSystem &chatSystem) {

  std::cout << prompt << std::endl;

  while (true) {
    try {
      std::string inputData;
      if (!std::getline(std::cin, inputData)) {
        continue;
      };
      if (inputData.empty()) {
        std::cerr << "Вы ничего не ввели. Попробуйте еще раз." << std::endl;
        continue;
      }
      if (inputData == "0") {
        userData = inputData;
        break;
      }

      if (newUserData) {

        checkInputNewData(inputData, passwordLengthMin, passwordLengthMax,
                          isPassword);
        userData = inputData;
        break;
      } else {
        if (!isPassword &&
            !checkIsUserDataInSystem(inputData, chatSystem, false)) {
          std::cerr << "Вы ввели неправильный логин. Попробуйте другой."
                    << std::endl;
          continue;
        } else if (isPassword &&
                   !checkIsUserDataInSystem(inputData, chatSystem, true)) {
          std::cerr << "Вы ввели неправильный пароль. Попробуйте другой."
                    << std::endl;
          continue;
        } else
          userData = inputData;
        break;
        break;
      }
    } catch (const std::exception &ex) {
      std::cerr << ex.what() << std::endl;
    }
  }
}

bool checkIsUserDataInSystem(const std::string &userData,
                             const ChatSystem &chatSystem, bool password) {
  if (!password) {
    for (const auto &user : chatSystem.getUsers()) {
      if (user->getLogin() == userData) {
        return true;
      }
    }
  } else {
    for (const auto &user : chatSystem.getUsers()) {
      if (user->getPassword() == userData) {
        return true;
      }
    }
  }
  return false;
  ;
};

/**
 * @brief Запрашивает у пользователя новый логин и валидирует его.
 */
void inputNewLogin(std::string &login, const ChatSystem &chatSystem) {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    inputDataValidation(
        "Введите новый Логин либо 0 для выхода в предыдущее меню. Логин не "
        "менее 5 "
        "символов и не более 20 символов (можно использовать только латинские "
        "буквы и цифры) - ",
        5, 20, false, login, true, chatSystem);

    if (login == "0") {
      break;
    };
    if (checkIsUserDataInSystem(login, chatSystem, false)) {
      std::cerr << "Логин уже занят. Попробуйте другой." << std::endl;
      continue;
    } else
      break;
  }
}

/**
 * @brief Запрашивает у пользователя новый пароль и валидирует его.
 */
void inputNewPassword(std::string &password, const ChatSystem &chatSystem) {

  inputDataValidation(
      "Введите новый Пароль либо 0 для выхода в предыдущее меню. Пароль не "
      "менее 5 символов и не более 10, "
      "обязательно использовать минимум одну заглавную букву и одну цифру "
      "(можно использовать только латинские буквы и цифры) - ",
      5, 10, true, password, true, chatSystem);
}
/**
 * @brief Запрашивает у пользователя нновое имя проверяет его.
 */
void inputNewName(std::string &name, const ChatSystem &chatSystem) {
  inputDataValidation(
      "Введите желаемое Имя для отображения, не менее 3 символов и не более "
      "10, (можно использовать только латинские буквы и цифры) - ",
      3, 10, false, name, true, chatSystem);
}

/**
 * @brief Основная функция регистрации нового пользователя.
 *
 * Выводит вступительное сообщение, затем вызывает функции для получения логина
 * и пароля.
 */
void userRegistration(ChatSystem &chatSystem) {
  std::cout << "Регистрация нового пользователя." << std::endl;

  UserData userData;

  inputNewLogin(userData._login, chatSystem);
  if (userData._login == "0")
    return;
  ;
  inputNewPassword(userData._password, chatSystem);
  if (userData._password == "0")
    return;
  ;
  inputNewName(userData._name, chatSystem);
  if (userData._name == "0")
    return;
  ;

  //   userData._login = "Yan2201";
  //   userData._password = "qwert54S";
  //   userData._name = "Yan";

  // сначала делаем указатель на нового юзера
  auto newUser_ptr = std::make_shared<User>(userData._login, userData._name,
                                            userData._password);

  // добавляем пользователя в систему
  chatSystem.addUser(newUser_ptr);

  // устанавливаем активного пользователя в системе
  chatSystem.setActiveUser(newUser_ptr);

  chatSystem.getActiveUser()->showUserData();

  // создаем список чатов UserChatList и привязываем UserChatList к новому
  // пользователю
  newUser_ptr->createChatList(std::make_shared<UserChatList>(newUser_ptr));
}

bool userLoginInsystem(ChatSystem &chatSystem) {

  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  UserData userData;

  inputDataValidation("Введите Ваш логин, либо 0 для выхода: ", 0, 0, false,
                      userData._login, false, chatSystem);

  if (userData._login == "0")
    return false;
  else {
  }

  inputDataValidation("Введите Ваш пароль, либо 0 для выхода: ", 0, 0, true,
                      userData._password, false, chatSystem);

  if (userData._login == "0")
    return false;
  else
    return true;
};
