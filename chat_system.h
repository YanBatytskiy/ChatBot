#pragma once
#include "chat.h"
#include "user.h"
#include <memory>
#include <vector>

class ChatSystem {
private:
  std::vector<std::shared_ptr<User>> _users;
  std::vector<std::shared_ptr<Chat>> _chats;

public:
  // constructors
  ChatSystem();
  ~ChatSystem() = default;

  // getters
  const std::vector<std::shared_ptr<User>> &getUsers() const;

  const std::vector<std::shared_ptr<Chat>> &getChats() const;

  // Add
  void addUser(const std::shared_ptr<User> &user);
  void addChat(const std::shared_ptr<Chat> &chat);

  // removers
  void eraseUser(const std::shared_ptr<User>& user);
  void eraseChat(const std::shared_ptr<Chat>& chat);
};