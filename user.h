#pragma once
#include <string>

class User {
private:
  std::string _login;
  std::string _userName;
  std::string _password;

public:
  // constructors
  User(const std::string& login, const std::string& userName, const std::string& password);
  ~User()=default;

  // getters
  std::string getLogin() const;
  std::string getUserName() const;
  std::string getPassword() const;

  // setters
  void setLogin(const std::string& login);
  void setUserName(const std::string& userName);
  void setPassword(const std::string& password);

  // additional methods
  bool checkPassword(const std::string& password) const;
  bool checkLogin(const std::string& login) const;
  void showUserData() const;
};