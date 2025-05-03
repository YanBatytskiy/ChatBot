#pragma once
#include "validation_exception.h"

class LoginException : public ValidationException {
public:
  explicit LoginException(const std::string &message) : ValidationException("Sign In Exception: " + message) {};
};

class UserNotFoundException : public LoginException {
public:
  UserNotFoundException() : LoginException("!!!Такой пользователь не найден. ") {};
};

class IncorrectPasswordException : public LoginException {
public:
  IncorrectPasswordException() : LoginException("!!!Неверный пароль.") {};
};