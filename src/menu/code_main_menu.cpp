/**
 * @file code_auth_menu.cpp
 * @brief Реализация начального меню авторизации ChatBot 'Shark'
 * @version 1.0
 * @date 2025
 */
#include "menu/code_init_system.h"
#include "system/chat_system.h"
#include "user/user_chat_list.h"

#include <cctype>
#include <iostream>
#include <limits>
#include <ostream>

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

void menuListOpenChat1(ChatSystem &chatSystem, const std::shared_ptr<Chat> &chat, std::size_t unReadCountIndex) {

  // ДОДЕЛАТЬ

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
        std::cerr << "Вы ничего не ввели. Попробуйте еще раз." << std::endl;
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

void mainMenuList2(ChatSystem &chatSystem) {

  auto chatCount = chatSystem.getActiveUser()->getUserChatList()->getChatFromList().size();

  while (true) {
    std::cout << std::endl;

	
    chatSystem.getActiveUser()->printChatList(chatSystem.getActiveUser());
    std::cout << std::endl << "всего: " << chatCount;
    std::cout << std::endl;

    if (chatSystem.getActiveUser()->getUserChatList()->getChatFromList().empty()) return;
	
    std::cout << "Выберите пункт меню: " << std::endl;
    std::cout << "От 1 до " << chatCount << " - Чтобы открыть чат введите его номер (всего " << chatCount
              << " чата(ов)): " << std::endl;
    std::cout << "f - Поиск по чатам." << std::endl;
    std::cout << "0 - Выйти в предыдущее меню" << std::endl;

    std::string userChoiceList2;
    std::size_t chatNumber;

    while (true) {
      std::getline(std::cin, userChoiceList2);
      if (userChoiceList2.empty()) {
        std::cerr << "Вы ничего не ввели. Попробуйте еще раз.";
        continue;
      }

      try {
        chatNumber = std::stoull(userChoiceList2);
      } catch (const std::exception &e) {
        std::cerr << "Вы ввели неправильные данные. Попробуйте еще раз." << std::endl;
        continue;
      }
      if (chatNumber < 0 || chatNumber > chatCount) {
        std::cerr << "Вы ввели неправильные данные. Попробуйте еще раз." << std::endl;
        continue;
      } else
        break;
    } // второй while

    if (chatNumber == 0) {
      return;
    }
    if (userChoiceList2 == "f") {
      std::cout << "Under constraction." << std::endl;
    }

    // здесь мы достаем из вектора количество непрочитанных сообщений для отображения на экране

    auto chatList = chatSystem.getActiveUser()->getUserChatList()->getChatFromList(); // weak указатель на вектор
    if (!chatList.empty()) {
      auto activeChat_weak = chatList[chatNumber - 1];

      auto activeChat_ptr = activeChat_weak.lock();
      if (activeChat_ptr) {
        menuListOpenChat1(chatSystem, activeChat_ptr, chatNumber - 1); // выводим чат и вызываем следующее меню
      } else
        std::cerr << "Ошибка. Нет такого чата." << std::endl;
    } else {
      std::cerr << "Ошибка. Нет чатов у Пользоывателя." << std::endl;
      continue;
    }

  } // первый while
}

//
//
//

void mainMenuChoice(ChatSystem &chatSystem) { // вывод главного меню
  short userChoiceMain;

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

    bool exit = true;
    while (exit) {
      if (!(std::cin >> userChoiceMain)) {
        std::cout << "Ошибка ввода. Попробуйте еще раз." << std::endl;
        std::cin.clear(); // сбрасываем флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Очищаем буфер ввода
        continue;
      }

      if (userChoiceMain < 0 || userChoiceMain > 4) {
        std::cout << "Вы ввели неправильное число. Попробуйте еще раз." << std::endl;
        continue;
      } else {
        switch (userChoiceMain) {
        case 0:
          return;
          break; // case 0 MainMenu
        case 1:
          std::cout << "Under constraction." << std::endl;
          break; // case 1 MainMenu
        case 2:
          std::cin.clear(); // сбрасываем флаг ошибки
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                          '\n'); // Очищаем буфер ввода
          mainMenuList2(chatSystem);
          exit = false;
          continue;
          break; // case 2 MainMenu
        case 3:
          std::cout << "Under constraction." << std::endl;
          break; // case 3 MainMenu
        case 4:
          std::cout << "Under constraction." << std::endl;
          break; // case 4 MainMenu
        default:
          break; // default MainMenu
        }
      }
    }
  } // second
}

void inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat, std::size_t unReadCountIndex) {
  std::cout << std::endl << "Наберите новое сообщение либо 0 для выхода:" << std::endl;
  std::string inputData;

  while (true) {
    std::cin.clear(); // сбрасываем флаг ошибки

    std::getline(std::cin, inputData);
    if (inputData.empty()) {
      std::cout << "Вы ничего не ввели. Попробуйте еще раз." << std::endl;
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