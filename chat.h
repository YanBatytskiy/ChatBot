#pragma once

#include "message.h"
#include <vector>

class Chat {
private:
  std::vector<std::shared_ptr<IMessage>> _messages;

public:
  // without constructor and destructor becouse vector has own ones

  // add message to chat
  void addMessage(const std::shared_ptr<IMessage> &message) {
    _messages.push_back(message);
  };

  // get message from chat
  const std::vector<std::shared_ptr<IMessage>> &getMessages() const {
    return _messages;
  }
};