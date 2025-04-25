#pragma once
#include "chat_system.h"
#include <string>

// структура для автоматизации задания истории чатов
struct InitDataArray {
  std::string _messageText;
  std::string _timeStamp;
  std::shared_ptr<User> _sender;
  std::vector<std::shared_ptr<User>> _recipients;

  InitDataArray(std::string messageText, std::string timeStamp,
                std::shared_ptr<User> sender,
                std::vector<std::shared_ptr<User>> _recipients);

  virtual ~InitDataArray() = default;
};

void systemInitTest(ChatSystem &_chatsystem);