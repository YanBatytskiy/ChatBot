/**
 * @file code_auth_menu.cpp
 * @brief Реализация начального меню авторизации ChatBot 'Shark'
 * @version 1.0
 * @date 2025
 */
#include "exception/validation_exception.h"
#include "system/chat_system.h"
#include "system/system_function.h"

#include "menu/2_0_login_menu.h"
#include "menu/2_1_new_chat_menu.h"
#include "menu/2_2_chat_list_menu.h"
#include "menu/2_4_user_profile.h"

#include <cctype>
#include <iostream>
#include <ostream>

/**
 * @brief Отображает главное меню авторизации и получает выбор пользователя.
 *
 * Меню предлагает пользователю зарегистрироваться, войти или завершить работу.
 *
 * @return short Выбор пользователя:
 * - 1 — Регистрация пользователя,
 * - 2 — Вход в чат,
 * - 0 — Завершение программы.
 */
short authMenu() { // вывод главного меню

  while (true) {

    std::cout << std::endl << "ChatBot 'Shark' Версия 1.0. @2025 \n \n";

    std::cout << "Выберите пункт меню: " << ::std::endl
              << "1. Регистрация пользователя " << std::endl
              << "2. Войти в ЧатБот" << std::endl
              << "0. Завершить программу" << std::endl;

    std::string userChoice;
    int userChoiceNumber;

    while (true) {

      std::getline(std::cin, userChoice);
      try {

        if (userChoice.empty())
          throw EmptyInputException();

        if (userChoice == "0")
          return 0;

        userChoiceNumber = parseGetlineToInt(userChoice);

        if (userChoiceNumber != 1 && userChoiceNumber != 2)
          throw IndexOutOfRangeException(userChoice);

        return userChoiceNumber;

      } catch (const ValidationException &ex) {
        std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
        continue;
      }
    } // first while
  } // second while
}
//
//
//

void loginMenuChoice(ChatSystem &chatSystem) { // вывод главного меню

  // доделать - продумать передачу по конст ссылке ChatSystem и дополнительный аргумент для изменеиня

  int userChoiceNumber;
  std::string userChoice;

  while (true) {
    std::cout << std::endl;
    std::cout << "Добрый день, пользователь " << chatSystem.getActiveUser()->getUserName() << std::endl;
    std::cout << std::endl;
    std::cout << "Выберите пункт меню: " << std::endl;
    std::cout << "1 - Создать новый чат" << std::endl;
    std::cout << "2 - Показать список чатов" << std::endl;
    std::cout << "3 - Показать список папок - Under constraction." << std::endl;
    std::cout << "4 - Показать Профиль пользователя" << std::endl;
    std::cout << "0 - Выйти в предыдущее меню" << std::endl;

    bool exit2 = true;
    while (exit2) {
      std::getline(std::cin, userChoice);
      try {

        if (userChoice.empty())
          throw EmptyInputException();

        if (userChoice == "0")
          return;

        userChoiceNumber = parseGetlineToInt(userChoice);

        if (userChoiceNumber < 0 || userChoiceNumber > 4)
          throw IndexOutOfRangeException(userChoice);

        switch (userChoiceNumber) {
        case 1:
          LoginMenu_1NewChat(chatSystem);
          exit2 = false;
          continue;
        //   break; // case 1 MainMenu
        case 2:
          loginMenu_2ChatList(chatSystem);
          exit2 = false;
          continue;
          break; // case 2 MainMenu
        case 3:
          std::cout << "Показать список папок - Under constraction." << std::endl;
          break; // case 3 MainMenu
        case 4:
          loginMenu_4UserProfile(chatSystem);
          exit2 = false;
          continue;
          break; // case 4 MainMenu
        default:
          break; // default MainMenu
        } // switch

      } // try
      catch (const ValidationException &ex) {
        std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
        continue;
      }
    } // second
  }
}