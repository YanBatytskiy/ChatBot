#pragma once
// #include "user.h"
#include "chat.h"
#include <memory>
#include <vector>

class User;

class UserChatList {
private:
  std::shared_ptr<User> _owner;
  std::vector<std::shared_ptr<Chat>> _chatsList;
  std::vector<std::size_t> _lastReadIndex; // номер последнего прочитанного
                                           // сообщения для каждого чата

public:
  // constructors
  UserChatList(const std::shared_ptr<User> &owner);
  ~UserChatList() = default;

  // getters
  std::shared_ptr<User> getOwner() const;
  std::vector<std::shared_ptr<Chat>> getChatsList() const;
  std::vector<std::size_t> getLastIndexRead() const;

  // setters
  void addChat(const std::shared_ptr<Chat> &chat);

  // additional methods
  void makeAllRead(); // make all uread messages as read
};