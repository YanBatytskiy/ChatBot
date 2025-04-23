/// @brief регистрация нового пользователя
#include "code_user_reg.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <memory>

/// @brief input checking
bool checkInputNewLoginPassword(const std::string &inputData,
                                std::size_t passwordLengthMin,
                                std::size_t passwordLengthMax, bool password) {

  std::unique_ptr<char[]> inputData_ptr =
      std::make_unique<char[]>(inputData.length() + 1);

  if (inputData.length() < passwordLengthMin ||
      inputData.length() > passwordLengthMax) {
    std::cout << "Количество символов (" << inputData.length()
              << ") некорректно"
              << ", пожалуйста попробуйте ввести еще раз:" << std::endl;
    return false;
  }

  std::strcpy(inputData_ptr.get(),
              inputData.c_str()); // копируем строку в массив

  bool isCapital = false;
  bool isNumber = false;
  bool wrongSymbol = false;
  char wrongChar;

  // проверяем ввод логина на корректность символов
  for (auto i = 0u; i < inputData.length(); ++i) {
    if (!std::isalnum(inputData_ptr[i])) {
      wrongChar = inputData_ptr[i];
      wrongSymbol = true;
      break;
    }
    if (std::isdigit(inputData_ptr[i]))
      isNumber = true;
    if (std::isupper(inputData_ptr[i]))
      isCapital = true;
  }

  if (wrongSymbol) {
    std::cout << std::endl
              << "Должны быть только буквы и цифры, символ '" << wrongChar;
    std::cout << "' не допустим, пожалуйста попробуйте ввести еще раз:"
              << std::endl;
    return false;
  }
  if (!isCapital && password) {
    std::cout << std::endl
              << "Должна быть хотя бы одна заглавная буква, "
                 "пожалуйста попробуйте ввести еще раз:"
              << std::endl;
    return false;
  }
  if (!isNumber && password) {
    std::cout << std::endl
              << "Должна быть минимум одна цифра, "
                 "пожалуйста попробуйте ввести еще раз:"
              << std::endl;
    return false;
  }

  return true;
}

void inputNewLogin() {
  std::string inputData;

  std::cout << "Введите желаемое имя Логина, не менее 5 символов и не более 20 "
               "символов(можно использовать только "
               "латинские буквы и цифры) - "
            << std::endl;

  do {
    std::cin >> inputData;

  } while (!checkInputNewLoginPassword(inputData, 5, 20, false));
}

void inputNewPassword() {
  std::string inputData;
  std::cout << "Введите желаемый Пароль, не менее 5 символов и не более 10, "
               "обязательно использовать минимум одну заглавную букву и одну "
               "цифру (можно использовать только "
               "латинские буквы и цифры) - "
            << std::endl;

  do {
    std::cin >> inputData;

  } while (!checkInputNewLoginPassword(inputData, 5, 10, true));
}

void userRegistration() { /// @brief регистрация нового пользователя
  std::cout << "Регистрация нового пользователя. " << std::endl;

  inputNewLogin();
  inputNewPassword();
};