#pragma once
#include "my_exception.h"

class ValidationException : public MyException {
public:
  explicit ValidationException(const std::string &message) : MyException("Validation Exception: " + message) {};
};

class EmptyInputException : public ValidationException {
public:
  EmptyInputException() : ValidationException("!!!Вы ничего не ввели.") {};
};

class InvalidCharacterException : public ValidationException {
public:
  InvalidCharacterException(const char &ch)
      : ValidationException(std::string("!!!Недопустимый символ '") + ch + "'") {};
};

class IndexOutOfRangeException : public ValidationException {
public:
  IndexOutOfRangeException(const std::string &st)
      : ValidationException(std::string("!!!Ввод '" + st + "' вне допустимого диапазона.")) {};
  IndexOutOfRangeException(const char &st)
      : ValidationException(std::string("!!!Ввод '") + st + "' вне допустимого диапазона.") {};
};

class InvalidQuantityCharacterException : public ValidationException {
public:
  InvalidQuantityCharacterException() : ValidationException("!!!Некорректное количество символов.") {};
};

class NonCapitalCharacterException : public ValidationException {
public:
  NonCapitalCharacterException() : ValidationException("!!!Требуется заглавная буква.") {};
};

class NonDigitalCharacterException : public ValidationException {
public:
  NonDigitalCharacterException() : ValidationException("!!!Требуется цифра.") {};
};

class ChatNotFoundException : public ValidationException {
	public:
	ChatNotFoundException() : ValidationException("!!!Ошибка. Чат не найден. Обратитесь к администратору") {};
	};