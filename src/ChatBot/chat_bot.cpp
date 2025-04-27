#include "menu/code_init_system.h"
#include "menu/code_main_menu.h"
#include "menu/code_registration.h"
#include "system/chat_system.h"
#include <iostream>

int main() {

  // создаем ChatSystem1
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
      //
      //

      //   switch (userChoiceMainMenu) {
      //   case 0:
      //     break; // case 0 MainMenu
      //   case 1:
      //     std::cout << "Under constraction." << std::endl;
      //     break; // case 1 MainMenu
      //   case 2:
      //     std::cin.clear(); // сбрасываем флаг ошибки
      //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
      //                     '\n'); // Очищаем буфер ввода

      //     mainMenuList2(chatSystem);
      //     break; // case 2 MainMenu
      //   case 3:
      //     std::cout << "Under constraction." << std::endl;
      //     break; // case 3 MainMenu
      //   case 4:
      //     std::cout << "Under constraction." << std::endl;
      //     break; // case 4 MainMenu
      //   default:
      //     break; // default MainMenu
      //   }
      //
      //
      break; // case 2 AuthMenu
    }
    default:
      break; // default AuthMenu
    }
  }
  std::cout << std::endl;
  return 0;
}