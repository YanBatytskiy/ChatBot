#include "chat_system.h"
#include "code_auth_menu.h"
#include "code_init_system.h"
#include "code_main_menu.h"
#include "code_registration.h"
#include <iostream>

// #include "chat.h"
// #include "message.h"
// #include "message_content.h"  //   recipients.push_back(Elena1510_ptr);

// #include "message_content_struct.h"
// #include "user.h"
// #include "user_chat_list.h"
// #include <memory>
// #include <vector>

int main() {

  // создаем ChatSystem1
  ChatSystem chatSystem;

  systemInitTest(chatSystem);

  short userChoice;

  while (true) {
    chatSystem.setActiveUser(nullptr);
    userChoice = authMenu();

    // запуск регистрации или логина в систему либо выход
    switch (userChoice) {
    case 0: // выход
      return 0;
      break;
    case 1: // регистрация нового пользователя
      userRegistration(chatSystem);
      break;
    case 2: { // вход пользователя в систему
              //   if (userLoginInsystem(chatSystem))
      std::shared_ptr<User> activeUser_ptr =
          findUserbyLogin("Alex2104", chatSystem);

      chatSystem.setActiveUser(activeUser_ptr);
      mainhMenu(chatSystem);
    } break;
    default:
      break;
    }
  }
  std::cout << std::endl;
  return 0;
}