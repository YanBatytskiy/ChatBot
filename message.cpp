#include "message.h"
#include "message_content.h"
#include "message_content_struct.h"
#include <iostream>
#include <memory>

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

void Message::printMessage(const std::shared_ptr<User> &currentUser) {
  auto sender = _sender.lock();
  if (!sender)
    return;

  bool messageDirection = (sender == currentUser);

  if (!messageDirection) { // income Message

    std::cout << "\033[32m"; // red
    std::cout << "                     -> Входящее от "
              << currentUser->getUserName() << "    " << _time_stamp
              << std::endl;

    for (const auto &content : _content) {
      if (auto textContent =
              std::dynamic_pointer_cast<MessageContent<TextContent>>(content)) {
        std::cout << textContent->getMessageContent()._text << std::endl;
      } else if (auto imageContent =
                     std::dynamic_pointer_cast<MessageContent<ImageContent>>(
                         content)) {
        std::cout << imageContent->getMessageContent()._image << std::endl;
      }
    }
  } else {

    std::cout << "\033[37m"; // white
    std::cout << "-< Исходящее: " << _time_stamp << std::endl;

    for (const auto &content : _content) {
      if (auto textContent =
              std::dynamic_pointer_cast<MessageContent<TextContent>>(content)) {
        std::cout << textContent->getMessageContent()._text << std::endl;
      } else if (auto imageContent =
                     std::dynamic_pointer_cast<MessageContent<ImageContent>>(
                         content)) {
        std::cout << imageContent->getMessageContent()._image << std::endl;
      }
    }
  }

  std::cout << "\033[0m";
};

// delete message will be realized further

// edit message will be realized further