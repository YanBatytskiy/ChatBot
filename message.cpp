#include "message.h"

// constructors
Message::Message(const std::vector<std::shared_ptr<IMessageContent>> &content,
                 const std::weak_ptr<User> &sender)
    : _content(content), _sender(sender), _time_stamp("вторник 22-апр 2025.") {}

// getters
// get content of the message
const std::vector<std::shared_ptr<IMessageContent>> &
Message::getContent() const {
  return _content;
}

// get Sender of the message
std::weak_ptr<User> Message::getSender() const { return _sender; }

// get timeStamp of the message
const std::string &Message::getTimeStamp() const { return _time_stamp; }

// setters
// add content to the message
void Message::addContent(const std::shared_ptr<IMessageContent> &content) {
  _content.push_back(content);
}

void printMessage(const std::shared_ptr<User> &currentUser) {
}; // will be realized further

// delete message will be realized further

// edit message will be realized further