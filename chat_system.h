#pragma once
#include "chat.h"
#include "user.h"
#include <memory>
#include <vector>

class ChatSystem {
private:
  std::vector<std::shared_ptr<User>> _users;
  std::vector<std::shared_ptr<Chat>> _chats;
  std::shared_ptr<User> _activeUser;

public:
  // constructors
  ChatSystem();
  ~ChatSystem() = default;

  // getters
  const std::vector<std::shared_ptr<User>> &getUsers() const;

  const std::vector<std::shared_ptr<Chat>> &getChats() const;

  const std::shared_ptr<User> &getActiveUser() const;

  // setters
  void setActiveUser(const std::shared_ptr<User> user);

  // Add
  void addUser(const std::shared_ptr<User> &user);
  void addChat(const std::shared_ptr<Chat> &chat);

  // removers
  void eraseUser(const std::shared_ptr<User> &user);
  void eraseChat(const std::shared_ptr<Chat> &chat);
};