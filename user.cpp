#include "user.h"
#include <iostream>

// constructors
User::User(const std::string& login, const std::string& userName, const std::string& password)
    : _login(login), _userName(userName), _password(password) {}

// getters
std::string User::getLogin() const { return _login; }
std::string User::getUserName() const { return _userName; }
std::string User::getPassword() const { return _password; }

// setters
void User::setLogin(const std::string& login) { _login = login; }
void User::setUserName(const std::string& userName) { _userName = userName; }
void User::setPassword(const std::string& password) { _password = password; }

// additional methods
bool User::checkPassword( const std::string& password) const {
  return (password == _password);
}

bool User::checkLogin(const std::string& login) const {
  return (_login == login);
}

void User::showUserData() const {
  std::cout << "Name: " << _userName << ", Login: " << _login
            << ", Password: " << _password << std::endl;
}
