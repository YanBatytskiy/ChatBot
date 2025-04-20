#pragma once

#include "message.h"
#include <vector>

class Chat {
private:
  std::vector<std::shared_ptr<Message>> _messages;

public:
  // without constructor and destructor becouse vector has own ones

  // add message to chat
  void addMessage(const std::shared_ptr<Message> &message) {
    _messages.push_back(message);
  };

  // get message from chat
  const std::vector<std::shared_ptr<Message>> &getMessages() const {
    return _messages;
  }
};