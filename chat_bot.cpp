// #include "chat.h"
#include "chat_system.h"
// #include "message.h"
// #include "message_content.h"
// #include "message_content_struct.h"
// #include "user.h"
// #include "user_chat_list.h"

#include "code_auth_menu.h"
#include "code_init_system.h"
#include "code_user_reg.h"

#include <iostream>
// #include <memory>
// #include <vector>

int main() {

  short userChoice;
  userChoice = authMenu();

  // запуск регистрации или логина в систему либо выход
  switch (userChoice) {
  case 0: // выход
    return 0;
    break;
  case 1: // регистрация нового пользователя
    userRegistration();
    break;
  case 2: // вход пользователя в систему
    break;
  default:
    break;
  }

  // создаем ChatSystem
  ChatSystem chatSystem;

  // systemInintTest(chatSystem);

  std::cout << std::endl;
  return 0;
}