#include "system/chat_system.h"
#include "system/system_function.h"
#include <iostream>

// constructors
ChatSystem::ChatSystem(){};

// getters
const std::vector<std::shared_ptr<User>> &ChatSystem::getUsers() const { return _users; }

const std::vector<std::shared_ptr<Chat>> &ChatSystem::getChats() const { return _chats; }

const std::shared_ptr<User> &ChatSystem::getActiveUser() const { return _activeUser; }

// setters
void ChatSystem::setActiveUser(const std::shared_ptr<User> user) { _activeUser = user; }

// Add
void ChatSystem::addUser(const std::shared_ptr<User> &user) { _users.push_back(user); }

void ChatSystem::addChat(const std::shared_ptr<Chat> &chat) { _chats.push_back(chat); }

// removers
void ChatSystem::eraseUser(const std::shared_ptr<User> &user) {}
void ChatSystem::eraseChat(const std::shared_ptr<Chat> &chat) {}

// additional methods
std::size_t ChatSystem::showUserList(const bool showActiveUser) { // вывод на экрын списка пользователей
  std::cout << "Список пользователей:" << std::endl;
  size_t index = 1;
  size_t returnIndex;
  for (const auto &user : _users) {
    if (user == _activeUser) {
      returnIndex = index - 1;
    }
    if (!showActiveUser && user != _activeUser) {
      std::cout << index << ".  Имя - " << user->getUserName() << ", логин - " << user->getLogin() << ";" << std::endl;
      ++index;
    }
  }
  return returnIndex;
}

void ChatSystem::findUser(std::vector<std::shared_ptr<User>> &users,
                          const std::string &textToFind) { // поиск пользователя

  std::string textToFindLower = TextToLower(textToFind);

  // перебираем всех пользователей в векторе
  for (const auto &user : _users) {

    std::string LowerLogin = TextToLower(user->getLogin());
    std::string LowerName = TextToLower(user->getUserName());

    if (user != _activeUser)
      if (LowerLogin.find(textToFindLower) != std::string::npos || LowerName.find(textToFindLower) != std::string::npos)
        users.push_back(user);
  }
}