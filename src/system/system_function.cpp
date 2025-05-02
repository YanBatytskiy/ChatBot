#include "chat/chat.h"
#include "exception/validation_exception.h"
#include "system/chat_system.h"

#include "menu/0_init_system.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

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

std::size_t parseGetlineToSizeT(const std::string &str) { // конвертация из string в size_t
  try {
    unsigned long long value = std::stoull(str);

    if (value > static_cast<unsigned long long>(std::numeric_limits<int>::max())) {
      throw std::out_of_range("value exceeds size_t range");
    }
    return static_cast<std::size_t>(value);

  } catch (const std::invalid_argument &) {
    throw NonDigitalCharacterException();
  } catch (const std::out_of_range &) {
    throw IndexOutOfRangeException(str);
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