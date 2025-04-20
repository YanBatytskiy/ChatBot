#pragma once
#include "messageContent.h"
#include "user.h"
#include <memory>
#include <string>
#include <vector>

class IMessage { // interface for messages
public:
  virtual ~IMessage() = default;
};

// class for different type of messages
class Message : public IMessage {
private:
  std::vector<std::shared_ptr<IMessageContent>> _content;
  std::shared_ptr<User> _sender;
  std::vector<std::shared_ptr<User>> _recipients;
  std::string _time_stamp; // will be realized further

public:
  // constructors
  Message(const std::vector<std::shared_ptr<IMessageContent>> &content,
          const std::shared_ptr<User> &sender,
          const std::vector<std::shared_ptr<User>> &recipients)
      : _content(content), _sender(sender), _recipients(recipients),
        _time_stamp("will be realized further") {}

  ~Message() override = default; // destructor

  // getters
  // get content of the message
  std::vector<std::shared_ptr<IMessageContent>> &getContent() {
    return _content;
  }
  const std::vector<std::shared_ptr<IMessageContent>> &getContent() const {
    return _content;
  }

  // get Sender of the message
  std::shared_ptr<User> &getSender() { return _sender; }
  const std::shared_ptr<User> &getSender() const { return _sender; }

  // get recipients of the message
  std::vector<std::shared_ptr<User>> &getRecipients() { return _recipients; }
  const std::vector<std::shared_ptr<User>> &getRecipients() const {
    return _recipients;
  }

  // get timeStamp of the message
  std::string &getTimeStamp() { return _time_stamp; }
  const std::string &getTimeStamp() const { return _time_stamp; }

  // setters
  // add message
  void addContent(const std::shared_ptr<IMessageContent> &content) {
    _content.push_back(content);
  }

  // delete message will be realized further

  // edit message will be realized further

  void printMessage() {}; // will be realized further
};