#pragma once
#include "chat/chat.h"
#include "user/user.h"
#include <cstddef>
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

  // additional methods
  std::size_t showUserList(const bool showActiveUser); // вывод на экрын списка пользователей
  void findUser(const std::string userName);           // поиск пользователя
};