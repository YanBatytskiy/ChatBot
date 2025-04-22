#pragma once
#include "chat.h"
#include <memory>
#include <vector>

class User;

class UserChatList {
private:
  std::weak_ptr<User> _owner;
  std::vector<std::weak_ptr<Chat>> _chatList;
  std::vector<std::size_t> _lastReadIndex; // номер последнего прочитанного
                                           // сообщения для каждого чата

public:
  // constructors
  UserChatList(const std::shared_ptr<User> &owner);
  ~UserChatList() = default;

  // getters
  std::weak_ptr<User> getOwner() const;
  std::vector<std::weak_ptr<Chat>> getChatsList() const;
  std::vector<std::size_t> getLastIndexRead() const;

  // setters
  void addChat(const std::weak_ptr<Chat> &chat);

  // additional methods
  void makeAllRead(); // make all uread messages as read
};