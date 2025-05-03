#include "chat/chat.h"
#include "exception/validation_exception.h"
#include "message/message_content_struct.h"
#include "system/chat_system.h"

#include "menu/0_init_system.h"
#include "system/date_time_utils.h"

#include <algorithm>
#include <ctime>
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

void changeLastReadIndexForSender(const std::shared_ptr<User> &user, const std::shared_ptr<Chat> &chat) {

  chat->updateLastReadMessageIndex(user, chat->getMessages().size());
}

void addMessageToChat(const InitDataArray &initDataArray, std::shared_ptr<Chat> &chat) {

  std::vector<std::shared_ptr<IMessageContent>> iMessageContent;
  TextContent textContent(initDataArray._messageText);
  MessageContent<TextContent> messageContentText(textContent);
  iMessageContent.push_back(std::make_shared<MessageContent<TextContent>>(messageContentText));

  try {
    if (!initDataArray._sender) {
      throw UnknownException(" Отправитель отсутствует. Сообщение не будет создано. addMessageToChat");
    } else {
      Message message(iMessageContent, initDataArray._sender, initDataArray._timeStamp);

      chat->addMessage(std::make_shared<Message>(message));

      changeLastReadIndexForSender(initDataArray._sender, chat);
    };
  } catch (const ValidationException &ex) {
    std::cout << " ! " << ex.what() << std::endl;
  }
}

bool inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat) {
  std::cout << std::endl << "Наберите новое сообщение либо 0 для выхода:" << std::endl;
  std::string inputData;

  while (true) {
    try {
      std::getline(std::cin, inputData);

      if (inputData.empty())
        throw EmptyInputException();

      if (inputData == "0")
        return false;

      std::vector<std::shared_ptr<User>> recipients;
      for (const auto &participant : chat->getParticipants()) {
        auto user_ptr = participant._user.lock();
        if (user_ptr) {
          if (user_ptr != chatSystem.getActiveUser())
            recipients.push_back(user_ptr);
        }
      }

      InitDataArray newMessageStruct(inputData, getCurrentDateTime(), chatSystem.getActiveUser(), recipients);
      addMessageToChat(newMessageStruct, chat);
      return true;
    } // try
    catch (const ValidationException &ex) {
      std::cout << " ! " << ex.what() << " Попробуйте еще раз." << std::endl;
      continue;
    }
  } // while
}

std::string TextToLower(const std::string &str) {
  std::string result = str;

  // приводим всех к нижнему регистру
  std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
  return result;
}