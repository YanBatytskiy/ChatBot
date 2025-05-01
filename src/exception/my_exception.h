#pragma once
#include <string>

class MyException : public std::exception {
private:
  std::string _message;

public:
  explicit MyException(const std::string &message) : _message(message) {};
  const char *what() const noexcept override { return _message.c_str(); };
};