#pragma once
// #include "user_chat_list.h"
#include <memory>
#include <string>

class UserChatList;

class User {
private:
  std::string _login;
  std::string _userName;
  std::string _password;
  std::shared_ptr<UserChatList> _userChats;

public:
  // constructors
  User(const std::string &login, const std::string &userName,
       const std::string &password);
  ~User() = default;

  void createChatList(const std::shared_ptr<UserChatList> &chats);

  // getters
  std::string getLogin() const;
  std::string getUserName() const;
  std::string getPassword() const;
  std::shared_ptr<UserChatList> getUserChatList() const;

  // setters
  void setLogin(const std::string &login);
  void setUserName(const std::string &userName);
  void setPassword(const std::string &password);

  // additional methods
  bool checkPassword(const std::string &password) const;
  bool checkLogin(const std::string &login) const;
  void showUserData() const;
};