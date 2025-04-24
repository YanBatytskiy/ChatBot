#include "chat_system.h"

// constructors
ChatSystem::ChatSystem() {};

// getters
const std::vector<std::shared_ptr<User>> &ChatSystem::getUsers() const {
  return _users;
}

const std::vector<std::shared_ptr<Chat>> &ChatSystem::getChats() const {
  return _chats;
}

const std::shared_ptr<User> &ChatSystem::getActiveUser() const {
  return _activeUser;
}


// setters
void ChatSystem::setActiveUser(const std::shared_ptr<User> user) {
  _activeUser = user;
}

// Add
void ChatSystem::addUser(const std::shared_ptr<User> &user) {
  _users.push_back(user);
}

void ChatSystem::addChat(const std::shared_ptr<Chat> &chat) {
  _chats.push_back(chat);
}

// removers
void ChatSystem::eraseUser(const std::shared_ptr<User> &user) {};
void ChatSystem::eraseChat(const std::shared_ptr<Chat> &chat) {};
