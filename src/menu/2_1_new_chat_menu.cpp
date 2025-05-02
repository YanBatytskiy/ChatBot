#include "menu/2_1_new_chat_menu.h"
#include "chat/chat.h"
#include "exception/login_exception.h"
#include "exception/validation_exception.h"
#include "system/system_function.h"
#include "user/user.h"
#include "user/user_chat_list.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void LoginMenu_1NewChatMakeParticipants(ChatSystem &chatSystem, std::shared_ptr<Chat> &chat,
                                        std::size_t activeUserIndex,
                                        bool messageToAll) { // создение нового сообщения путем выбора пользователей

  std::string inputData;
  std::string userChoice;

  // выбираем - сообщение всем пользователям или нет
  if (messageToAll) {

    // заполняем вектор участников чата
    chat->addParticipant(chatSystem.getActiveUser());
    for (const auto &user : chatSystem.getUsers())
      if (user != chatSystem.getActiveUser()) {
        chat->addParticipant(user);
      }

    return;
  }

  // сообщение только некоторым пользователям

  bool exit = true;
  while (exit) {
    try {
      // получаем список получателей через ввод списка
      std::cout << "Введите номера пользователей через запятую или 0 для отмены: " << std::endl;

      getline(std::cin, inputData);

      if (inputData.empty())
        throw EmptyInputException();

      if (inputData == "0")
        continue;

      // проверяем на наличие недопустимых символов
      for (const auto &exactChar : inputData)
        if (!std::isdigit(exactChar) && static_cast<unsigned char>(exactChar) != ',')
          throw InvalidCharacterException(exactChar);

      std::cout << activeUserIndex << std::endl;

      // добавляем в конец запятую
      inputData.push_back(',');
      std::cout << std::endl << inputData << std::endl;

      // создаем вектор для хранения индексов получателей в массиве пользователей
      std::vector<std::size_t> recipientIndex;

      // заполняем вектор значениями
      std::string str_temp;
      std::size_t index_temp;

      do {
        auto pos = inputData.find_first_of(',');

        str_temp = inputData.substr(0, pos);
        //   std::cout << str_temp << " : ";

        if (!str_temp.empty()) {
          index_temp = parseGetlineToSizeT(str_temp);
          // std::cout << index_temp << std::endl;

          // проверяем на дубли
          if (index_temp <= activeUserIndex) {
            if (std::find(recipientIndex.begin(), recipientIndex.end(), index_temp - 1) == recipientIndex.end()) {
              recipientIndex.push_back(index_temp - 1);
              // std::cout << " : " << index_temp - 1 << std::endl;
            }
          } else {
            if (std::find(recipientIndex.begin(), recipientIndex.end(), index_temp) == recipientIndex.end()) {
              recipientIndex.push_back(index_temp);
              std::cout << " : " << recipientIndex.back() << std::endl;
            };
          };
        };

        inputData.erase(0, pos + 1);
      } while (!inputData.empty());

      // проверка временная
      std::cout << std::endl;
      for (const auto &rep : recipientIndex)
        std::cout << rep << ", ";

      // проверка временная
      std::cout << std::endl;
      for (std::size_t i = 1; i <= recipientIndex.size(); ++i) {
        std::cout << chatSystem.getUsers()[recipientIndex[i - 1]]->getLogin() << ", ";
      }

      // добавляем отправителя в вектор участников
      chat->addParticipant(chatSystem.getActiveUser());

      // заполняем вектор вектор участников
      for (const auto &recipient : recipientIndex) {
        chat->addParticipant(chatSystem.getUsers()[recipient]);
      }

      // проверки
      std::cout << "Получатели сообщений: " << std::endl;
      for (const auto &user : chat->getParticipants()) {
        auto user_ptr = user._user.lock();
        std::cout << user_ptr->getLogin() << " ака " << user_ptr->getUserName() << std::endl;
      }
    } // try
    catch (const ValidationException &ex) {
      std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
      continue;
    }
    exit = false;
  } // while
}
//
//
//
// общая функция для отправки сообщения в новый чат тремя способами
void CreateAndSendNewChat(ChatSystem &chatSystem, std::size_t activeUserIndex, bool sendToAll) {

};
//
//
//
void LoginMenu_1NewChat(ChatSystem &chatSystem) { // создание нового сообщения

  std::string userChoice;
  size_t userChoiceNumber;
  bool exit = true;

  while (exit) {
    std::cout << "Хотите: " << std::endl
              << "1. Найти пользователя - Under constraction." << std::endl
              << "2. Вывести весь список пользователей" << std::endl
              << "3. Отправить сообщение всем пользователям - Under constraction." << std::endl
              << "0. Для выхода в предыдущее меню" << std::endl;

    std::getline(std::cin, userChoice);

    try {

      if (userChoice.empty())
        throw EmptyInputException();

      if (userChoice == "0")
        return;

      userChoiceNumber = parseGetlineToInt(userChoice);

      if (userChoiceNumber != 1 && userChoiceNumber != 2 && userChoiceNumber != 3)
        throw IndexOutOfRangeException(userChoice);

      switch (userChoiceNumber) {
      case 1: {
        //   chatSystem.findUser("1");
        std::cout << "1. Найти пользователя - Under constraction." << std::endl;
        continue;
        break; // case 1
      }
      case 2: { // 2. Вывести весь список пользователей

        // запомнили номер активного пользователя
        auto activeUserIndex = chatSystem.showUserList(false);

        // создали новый чат
        auto chat = std::make_shared<Chat>();

        // определили получателей и участников чата, чат возврашается с заполненным массивом участников, а получатели
        // заполняются в inputNewMessage
        LoginMenu_1NewChatMakeParticipants(chatSystem, chat, activeUserIndex, false);

        std::cout << std::endl << "Вот твой чат. В нем всего 0 сообщения(ий). " << std::endl;

        bool exitCase2 = true;
        std::size_t unReadCount = 0;

        while (exitCase2) {
          try {
            if (inputNewMessage(chatSystem, chat) == false) { // пользователь решмил не вводить сообщение
              exitCase2 = false;
            } else { // пользователь ввел сообщение
              if (unReadCount == 0) {
                // добавили в головную систему чтобы не потерять чат при выходе из метода
                chatSystem.addChat(chat);

                // добавили каждому участнику чат в чат-лист
                for (const auto &user : chat->getParticipants()) {
                  auto user_ptr = user._user.lock();
                  if (user_ptr) {
                    user_ptr->getUserChatList()->addChat(chat);
                  } else
                    throw BadWeakException("LoginMenu_1NewChat");
                }
              }
              ++unReadCount;

              // проверки
              chat->printChat(chatSystem.getActiveUser());
              // std::cout << std::endl;
            }; // else
          } // try
          catch (const ValidationException &ex) {
            std::cout << " ! " << ex.what() << std::endl;
          }
        } // while case 2
        exit = false; // выход в верхнее меню так как новый чат уже не новый
        break;        // case 2
      }
      case 3: {

        auto chat_ptr = std::make_shared<Chat>();
        LoginMenu_1NewChatMakeParticipants(chatSystem, chat_ptr, 0, true);
        break; // case 3
      }
      default:
        break; // default
      } // switch
    } // try
    catch (const ValidationException &ex) {
      std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
      continue;
    }
  } // while
}