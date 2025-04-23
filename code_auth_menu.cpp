#include "code_auth_menu.h"
#include <iostream>
#include <limits>

void StartSystem() {
  ; // start system
}

short authMenu() { // вывод главного меню
  std::cout << "ChatBot 'Shark' Версия 1.0. @2025 \n \n";
  short userChoice;

  for (;;) {
    userChoice = 0;
    std::cout << "Выберите пункт меню: \n1 - Регистрация пользователя \n2 - "
                 "Войти в ЧатБот \n0 - Завершить программу"
              << std::endl;
    std::cin >> userChoice;

    if (userChoice == 0) {
      std::cout << "До свидания!" << std::endl << std::endl;
      break;
    } else if (userChoice != 1 && userChoice != 2) {
      std::cout << "Вы ввели неправильное число. Попробуйте еще раз."
                << std::endl;
      std::cin.clear(); // сбрасываем флаг ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Очищаем буфер ввода
    }
    else break;
  }

  return userChoice;
};