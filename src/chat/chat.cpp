#include "chat/chat.h"
#include <iostream>
// #include <iterator>

Chat::Chat(const std::vector<std::weak_ptr<User>> &participients)
    : _participients(participients) {}; // constructor for an empty chat. not initilize_messagess becouse
                                        // constructor of vector will make it empty automatically

// add message to chat
void Chat::addMessage(const std::shared_ptr<Message> &message) { _messages.push_back(message); }

// get message from chat
const std::vector<std::shared_ptr<Message>> &Chat::getMessages() const { return _messages; }

// get participients of the chat
const std::vector<std::weak_ptr<User>> &Chat::getParticipients() const { return _participients; }

// print full chat
void Chat::printChat(const std::shared_ptr<User> &currentUser) {
  if (!_messages.empty()) {
    for (const auto &message : _messages) {
      message->printMessage(currentUser);
    }
  } else
    std::cout << "Cообщуний нет." << std::endl;
};
