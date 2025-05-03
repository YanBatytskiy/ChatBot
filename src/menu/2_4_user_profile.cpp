#include "2_4_user_profile.h"
#include "exception/validation_exception.h"
#include "menu/1_registration.h"
#include "system/chat_system.h"
#include "system/system_function.h"
#include <iostream>

void userNameChange(ChatSystem &chatSystem) { // смена имени пользователя

  UserData userData;

  inputNewName(userData, chatSystem);
  if (userData._name.empty())
    return;

  chatSystem.getActiveUser()->setUserName(userData._name);

  std::cout << "Имя изменено. Логин  = " << chatSystem.getActiveUser()->getLogin()
            << " и Имя = " << chatSystem.getActiveUser()->getUserName() << std::endl;
}

void userPasswordChange(ChatSystem &chatSystem) { // смена пароля пользователя

  UserData userData;

  inputNewPassword(userData, chatSystem);
  if (userData._password.empty())
    return;

  chatSystem.getActiveUser()->setPassword(userData._password);

  std::cout << "Пароль изменен. Логин = " << chatSystem.getActiveUser()->getLogin()
            << " и Имя = " << chatSystem.getActiveUser()->getUserName()
            << " и Пароль = " << chatSystem.getActiveUser()->getPassword() << std::endl;
}

// Профиль пользователя
void loginMenu_4UserProfile(ChatSystem &chatSystem) {
  int userChoiceNumber;
  std::string userChoice;

  while (true) {
    std::cout << std::endl;
    std::cout << "Добрый день, пользователь " << chatSystem.getActiveUser()->getUserName() << std::endl;
    std::cout << std::endl;
    std::cout << "Выберите пункт меню: " << std::endl;
    std::cout << "1 - Сменить имя пользователя (не логин)" << std::endl;
    std::cout << "2 - Сменить пароль - Under constraction." << std::endl;
    std::cout << "3 - Удалить все чаты пользователя - Under constraction." << std::endl;
    std::cout << "4 - Очистить все чаты пользователя - Under constraction." << std::endl;
    std::cout << "5 - Удалить Профиль пользователя - Under constraction." << std::endl;
    std::cout << "6 - Сменить аватарку пользователя - Under constraction." << std::endl;
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
          userNameChange(chatSystem);
          exit2 = false;
          break; // case 1 MainMenu
        case 2:
          userPasswordChange(chatSystem);
          exit2 = false;
          break; // case 2 MainMenu
        case 3:
          std::cout << "3 - Удалить все чаты пользователя - Under constraction." << std::endl;
          break; // case 3 MainMenu
        case 4:
          std::cout << "4 - Очистить все чаты пользователя - Under constraction." << std::endl;
          break; // case 4 MainMenu
        case 5:
          std::cout << "5 - Удалить Профиль пользователя - Under constraction." << std::endl;
          break; // case 5 MainMenu
        case 6:
          std::cout << "6 - Сменить аватарку пользователя - Under constraction." << std::endl;
          break; // case 6 MainMenu
        default:
          break; // default MainMenu
        } // switch

      } // try
      catch (const ValidationException &ex) {
        std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
        continue;
      }
    } // second while
  }
}
