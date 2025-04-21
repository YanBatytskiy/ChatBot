#pragma once

#include "message.h"
#include "user.h"
#include <vector>

class Chat {
private:
  std::vector<std::shared_ptr<User>> _participients;
  std::vector<std::shared_ptr<Message>> _messages;

public:
  Chat(const std::vector<std::shared_ptr<User>> &participients)
      : _participients(participients) {
        }; // constructor for an empty chat. not initilize_messagess becouse
           // constructor of vector will make it empty automatically
           
  virtual ~Chat() = default; // destructor

  // add message to chat
  void addMessage(const std::shared_ptr<Message> &message) {
    _messages.push_back(message);
  };

  // get message from chat
  const std::vector<std::shared_ptr<Message>> &getMessages() const {
    return _messages;
  }
};