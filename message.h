#pragma once
#include "user.h"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

class IMessage { // interface
public:
  virtual ~IMessage() = default;
};

// template for different type of messages
template <typename T> class Message : public IMessage {
private:
  T _content;
  std::shared_ptr<User> _sender;
  std::vector<std::shared_ptr<User>> _recipients;
  std::chrono::system_clock::time_point _dateTime;

public:
  // constructors
  Message(const T &content, const std::shared_ptr<User> &sender,
          const std::vector<std::shared_ptr<User>> &recipients)
      : _content(content), _sender(sender), _recipients(recipients),
        _dateTime(std::chrono::system_clock::now()) {}

  ~Message() override = default;

  // getters
  const T &getContent() const { return _content; }
  std::chrono::system_clock::time_point getDateTime() const {
    return _dateTime;
  }

  const std::shared_ptr<User> &getRe() const { return _sender; }
  const std::vector<std::shared_ptr<User>> &getRecipients() const {
    return _recipients;
  }
};