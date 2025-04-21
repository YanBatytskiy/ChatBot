#pragma once

class IMessageContent { // interface for template MessageContent
public:
  virtual ~IMessageContent() = default;
};

// template for message of one of the type (struct)
template <typename T> class MessageContent : public IMessageContent {
private:
  T _content; // will take type according to the used struct of message content

public:
  explicit MessageContent(const T &content)
      : _content(content) {}; // constructor
  // destructor will be inherited from interface IMessageContent

  T &getMessageContent() { return _content; };
  const T &getMessageContent() const { return _content; };

  void setMessageContent(const T &content) {
  }; // for edit of message, will be realized further
};