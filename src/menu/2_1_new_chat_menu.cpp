#include "menu/2_1_new_chat_menu.h"
#include "exception/validation_exception.h"
#include "system/system_function.h"
#include "user/user.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void LoginMenu_1NewChatMakeParticipients(ChatSystem &chatSystem,
                                         bool messageToAll) { // создение нового сообщения путем выбора пользователей

  std::string inputData;
  std::string userChoice;

  // запомнили номер активного пользователя
  auto activeUserIndex = chatSystem.showUserList(false);

  // выбираем - сообщение всем пользователям или нет
  if (messageToAll) {

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

      std::cout << std::endl;
      for (std::size_t i = 1; i <= recipientIndex.size(); ++i) {
        std::cout << chatSystem.getUsers()[recipientIndex[i - 1]]->getLogin() << ", ";
      }

      // создаем вектора получателей и участников нового чата
      std::vector<std::shared_ptr<User>> recipients;
      std::vector<std::weak_ptr<User>> participients;

      participients.push_back(chatSystem.getActiveUser()); // добавляем отправителя в вектор участников

      for (const auto &recipient : recipientIndex) {
        recipients.push_back(chatSystem.getUsers()[recipient]);
        participients.push_back(chatSystem.getUsers()[recipient]);
      }

      // проверки
      std::cout << std::endl;
      for (const auto &user : recipients) {
        std::cout << user->getLogin() << ", ";
      }

      // проверки
      std::cout << std::endl;
      for (const auto &user : participients) {
        auto user_ptr = user.lock();
        std::cout << user_ptr->getLogin() << ", ";
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
void LoginMenu_1NewChat(ChatSystem &chatSystem) { // создание нового сообщения

  std::string inputData;
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
        LoginMenu_1NewChatMakeParticipients(chatSystem, false);
        break; // case 2
      }
      case 3: {
        LoginMenu_1NewChatMakeParticipients(chatSystem, true);
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
    exit = false;
  } // while
}