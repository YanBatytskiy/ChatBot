/**
 * @file code_auth_menu.cpp
 * @brief Реализация начального меню авторизации ChatBot 'Shark'
 * @version 1.0
 * @date 2025
 */
#include "menu/code_main_menu.h"
#include "exception/validation_exception.h"
#include "menu/code_init_system.h"
#include "system/chat_system.h"
#include "user/user_chat_list.h"

#include <algorithm>
#include <any>
#include <cctype>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdexcept>

void inputNewMessage(ChatSystem &chatSystem, const std::shared_ptr<Chat> chat, std::size_t unReadCountIndex);

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

  std::cout << std::endl << "ChatBot 'Shark' Версия 1.0. @2025 \n \n";
  short userChoice;

  std::cout << "Выберите пункт меню: \n1 - Регистрация пользователя \n2 - "
               "Войти в ЧатБот \n0 - Завершить программу"
            << std::endl;

  while (true) {
    if (!(std::cin >> userChoice)) {
      std::cout << "Ошибка ввода. Попробуйте еще раз." << std::endl;
      std::cin.clear(); // сбрасываем флаг ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Очищаем буфер ввода
      continue;
    }

    if (userChoice == 0) {
      std::cout << "До свидания!" << std::endl << std::endl;
      break;
    } else if (userChoice != 1 && userChoice != 2) {
      std::cout << "Вы ввели неправильное число. Попробуйте еще раз." << std::endl;
      continue;
    }

    break;
  }
  return userChoice;
}
//
//
//

void mainMenuNewChat2(ChatSystem &chatSystem) { // создание нового сообщения

  std::string inputData;
  std::string userChoice;
  bool exit = true;

  while (exit) {
    std::cout << "Хотите: " << std::endl
              << "1. Воспользоваться поиском" << std::endl
              << "2. Вывести весь список пользователей?" << std::endl
              << "3. Отправить сообщение всем пользователям" << std::endl
              << "0. Для выхода в предыдущее меню" << std::endl;

    std::getline(std::cin, userChoice);

    try {

      if (userChoice.empty())
        throw EmptyInputException();

      if (userChoice == "0")
        return;

      if (userChoice != "1" && userChoice != "2" && userChoice != "3")
        throw IndexOutOfRangeException(userChoice);

      if (userChoice == "3") {
        std::cout << "3. Отправить сообщение всем пользователям. Under constraction." << std::endl;
        continue;
      }

      if (userChoice == "1") {
        chatSystem.findUser("1");
        continue;
      }

      // запомнили номер активного пользователя
      auto activeUserIndex = chatSystem.showUserList(false);

      // получаем список получателей через ввод списка
      std::cout << "Введите номера пользователей через запятую или 0 для отмены: " << std::endl;

      getline(std::cin, inputData);

      if (inputData.empty())
        throw EmptyInputException();

      if (inputData == "0")
        continue;

      for (const auto &exactChar : inputData) {
        if (!std::isdigit(exactChar) && static_cast<unsigned char>(exactChar) != ',') {
          throw IndexOutOfRangeException(exactChar);
        }
      }

      exit = false;
      // проверяем все символы на корректность

    } catch (const ValidationException &ex) { // блок try
      std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
      continue;
    }
  } // first while
}
//
//
//

void menuList2OpenChat1(ChatSystem &chatSystem, const std::shared_ptr<Chat> &chat /*, std::size_t unReadCountIndex*/) {

  // ДОДЕЛАТЬ в том числе исключения

  bool exit = true;
  while (exit) {
    auto messageCount = chat->getMessages().size();

    auto unReadCount = chat->getLastReadMessageIndex(chatSystem.getActiveUser());
    // получаем количество неппрочитанных

    std::cout << std::endl << "Вот твой чат. В нем всего " << messageCount << " сообщения(ий). ";
    std::cout << "\033[32m"; // red
    std::cout << "Из них непрочитанных - " << messageCount - unReadCount << std::endl;
    std::cout << "\033[0m";

    chat->printChat(chatSystem.getActiveUser());
    chat->updateLastReadMessageIndex(chatSystem.getActiveUser(), messageCount);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Что будем делать? " << std::endl;
    std::cout << "1 - написать сообщение" << std::endl;
    std::cout << "2 - удалить последние отправленные сообщения - Under constraction" << std::endl;
    std::cout << "3 - очистить чат - Under constraction" << std::endl;
    std::cout << "4 - выйти из чата/удалить чат у пользователя - Under constraction" << std::endl;
    std::cout << "5 - поиск внутри чата - Under constraction" << std::endl;
    std::cout << "0 - Выйти в предыдущее меню" << std::endl;

    std::string userChoice;
    size_t userChoiceNumber;

    bool exit2 = true;
    while (exit2) {
      std::getline(std::cin, userChoice);
      if (userChoice.empty()) {
        throw EmptyInputException();
        continue;
      } else if (userChoice == "0") {
        exit = false;
        break;
      };

      try {
        userChoiceNumber = std::stoull(userChoice);

      } catch (const std::exception &ex) {
        std::cerr << "Вы ввели неправильные данные. Попробуйте еще раз." << std::endl;
        continue;
      }
      if (userChoiceNumber < 1 || userChoiceNumber > 5) {
        std::cerr << "Вы ввели неправильные данные. Попробуйте еще раз." << std::endl;
        continue;
      };

      auto unReadCountIndex = chat->getLastReadMessageIndex(chatSystem.getActiveUser());
      switch (userChoiceNumber) {
      case 1:
        inputNewMessage(chatSystem, chat, unReadCountIndex);
        chat->updateLastReadMessageIndex(chatSystem.getActiveUser(), messageCount + 1);

        std::cout << std::endl;
        chat->printChat(chatSystem.getActiveUser());
        std::cout << std::endl;
        exit2 = false;
        break; // case 1
      case 2:
        std::cout << "Under constraction 2." << std::endl;
        break; // case 2
      case 3:
        std::cout << "Under constraction 3." << std::endl;
        break; // case 3
      case 4:
        std::cout << "Under constraction 4." << std::endl;
        break; // case 4
      case 5:
        std::cout << "Under constraction 5." << std::endl;
        break; // case 5
      default:
        break; // default
      } // switch
    } // second while
  } // first while
}
//
//
//

void mainMenuList2(ChatSystem &chatSystem) { // показать список чатов

  auto chatCount = chatSystem.getActiveUser()
                       ->getUserChatList()
                       ->getChatFromList()
                       .size(); // количество чатов у пользователя

  std::cout << std::endl;

  chatSystem.getActiveUser()->printChatList(chatSystem.getActiveUser()); // определяем текущего пользователя
  std::cout << std::endl;

  if (chatSystem.getActiveUser()->getUserChatList()->getChatFromList().empty()) {
    std::cout << "У пользователя пока нет чатов" << std::endl;
    return;
  }

  std::string userChoice;
  int userChoiceNumber;
  bool exit2 = true;

  while (true) {

    std::cout << "Выберите пункт меню: " << std::endl;
    std::cout << "От 1 до " << chatCount << " - Чтобы открыть чат введите его номер (всего " << chatCount
              << " чата(ов)): " << std::endl;
    std::cout << "f - Поиск по чатам." << std::endl;
    std::cout << "0 - Выйти в предыдущее меню" << std::endl;

    while (exit2) {
      std::getline(std::cin, userChoice);

      try {

        if (userChoice.empty())
          throw EmptyInputException();

        if (userChoice == "0")
          return;

        if (userChoice == "f") {
          std::cout << "Under constraction." << std::endl;
          exit2 = false;
          continue;
        }

        userChoiceNumber = parseGetlineToInt(userChoice);

        if (userChoiceNumber < 0 || userChoiceNumber > static_cast<int>(chatCount))
          throw IndexOutOfRangeException(userChoice);

        // здесь мы достаем из вектора количество непрочитанных сообщениотображения на экране
        auto chatList = chatSystem.getActiveUser()->getUserChatList()->getChatFromList(); // weak указатель на вектор

        auto activeChat_weak = chatList[userChoiceNumber - 1];
        auto activeChat_ptr = activeChat_weak.lock();

        if (!activeChat_ptr)
          throw ChatNotFoundException();
        else
          menuList2OpenChat1(chatSystem, activeChat_ptr);
      } catch (const ValidationException &ex) {
        std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
        continue;
      };
    }

  } // первый while
}

//
//
//

int parseGetlineToInt(const std::string &str) { // конвертация из string в int
  try {
    long long value = std::stoll(str);

    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
      throw std::out_of_range("value exceeds int range");
    }
    return static_cast<int>(value);

  } catch (const std::invalid_argument &) {
    throw NonDigitalCharacterException();
  } catch (const std::out_of_range &) {
    throw IndexOutOfRangeException(str);
  }
}

void mainMenuChoice(ChatSystem &chatSystem) { // вывод главного меню

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
    std::cout << "3 - Показать список папок" << std::endl;
    std::cout << "4 - Показать Профиль пользователя" << std::endl;
    std::cout << "0 - Выйти в предыдущее меню" << std::endl;

    bool exit2 = true;
    while (exit2) {
      std::getline(std::cin, userChoice);
      try {

        if (userChoice.empty()) {
          throw EmptyInputException();
        }

        if (userChoice == "0")
          return;

        userChoiceNumber = parseGetlineToInt(userChoice);

        if (userChoiceNumber < 0 || userChoiceNumber > 4)
          throw IndexOutOfRangeException(userChoice);
        else {

          switch (userChoiceNumber) {
          case 1:
            mainMenuNewChat2(chatSystem);
            exit2 = false;
            continue;
          //   break; // case 1 MainMenu
          case 2:
            mainMenuList2(chatSystem);
            exit2 = false;
            continue;
            break; // case 2 MainMenu
          case 3:
            std::cout << "Показать список папок - Under constraction." << std::endl;
            break; // case 3 MainMenu
          case 4:
            std::cout << "Показать Профиль пользователя -Under constraction." << std::endl;
            break; // case 4 MainMenu
          default:
            break; // default MainMenu
          } // switch
        } // else
      } // try
      catch (const ValidationException &ex) {
        std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
        continue;
      }
    } // second
  }
}

void inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat, std::size_t unReadCountIndex) {
  std::cout << std::endl << "Наберите новое сообщение либо 0 для выхода:" << std::endl;
  std::string inputData;

  while (true) {
    std::cin.clear(); // сбрасываем флаг ошибки

    std::getline(std::cin, inputData);
    if (inputData.empty()) {
      throw EmptyInputException();
      continue;
    } else if (inputData == "0") {
      return;
    }

    std::vector<std::shared_ptr<User>> recipients;
    for (const auto &participient : chat->getParticipients()) {
      auto user_ptr = participient._user.lock();
      if (user_ptr) {
        if (user_ptr != chatSystem.getActiveUser()) {
          recipients.push_back(user_ptr);
        }
      }
    }

    InitDataArray newMessageStruct(inputData, "15-04-2025, 15:00:00", chatSystem.getActiveUser(), recipients);
    addMessageToChat(newMessageStruct, chat);
    break;
    // std::cout << std::endl << "Тестовый вывод." << std::endl;
    // chat->printChat(chatSystem.getActiveUser());

  } // recipients
  ;
};