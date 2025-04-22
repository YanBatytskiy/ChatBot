#pragma once
#include "message_content.h"
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
  std::weak_ptr<User> _sender;
  std::string _time_stamp; // will be realized further

public:
  // constructors
  Message(const std::vector<std::shared_ptr<IMessageContent>> &content,
          const std::weak_ptr<User> &sender);

  ~Message() override = default; // destructor

  // getters
  // get content of the message
  const std::vector<std::shared_ptr<IMessageContent>> &getContent() const;

  // get Sender of the message
  std::weak_ptr<User> getSender() const;

  // get timeStamp of the message
  const std::string &getTimeStamp() const;

  // setters
  // add content to the message
  void addContent(const std::shared_ptr<IMessageContent> &content);

  void printMessage(const std::shared_ptr<User>& currentUser); 

  // delete message will be realized further

  // edit message will be realized further
};