#include "menu/code_init_system.h"
#include "menu/code_main_menu.h"
#include "menu/code_registration.h"
#include "system/chat_system.h"
#include <iostream>

int main() {

  // создаем ChatSystem
  ChatSystem chatSystem;

  systemInitTest(chatSystem);

  short userChoice;

  while (true) {
    chatSystem.setActiveUser(nullptr);
    // std::shared_ptr<User> activeUser_ptr = findUserbyLogin("E", chatSystem);
    // chatSystem.setActiveUser(activeUser_ptr);

    userChoice = authMenu();

    /*
     * @return short Выбор пользователя:
     * - 1 — Регистрация пользователя,
     * - 2 — Вход в чат,
     * - 0 — Завершение программы.
     */

    // запуск регистрации или логина в систему либо выход
    switch (userChoice) {
    case 0: // выход
      return 0;
      break;
    case 1: // регистрация нового пользователя
      userRegistration(chatSystem);
      break;
    case 2: { // вход пользователя в систему
      if (userLoginInsystem(chatSystem))
        mainMenuChoice(chatSystem);
      break; // case 2 AuthMenu
    }
    default:
      break; // default AuthMenu
    }
  }
  std::cout << std::endl;
  return 0;
}