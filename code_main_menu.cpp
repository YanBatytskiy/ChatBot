/**
 * @file code_auth_menu.cpp
 * @brief Реализация начального меню авторизации ChatBot 'Shark'
 * @version 1.0
 * @date 2025
 */
// #include "code_auth_menu.h"
#include <iostream>
#include <limits>

/**
 * @brief Отображает главное меню авторизации и получает выбор пользователя.
 *
 * Меню предлагает пользователю зарегистрироваться, войти или завершить работу.
 *
 * @return short Выбор пользователя:
 * - 1 — Регистрация пользователя,
 * - 2 — Вход в чат,
 * - 0 — Завершение программы.
 */
void mainhMenu() { // вывод главного меню
  short userChoice;

  std::cout << std::endl;
  std::cout << "Добрый день, пользователь " << 
  std::cout << "Выберите пункт меню: " << std::endl;
  std::cout << "1 - Создать новый чат" << std::endl;
  std::cout << "2 - Показать список чатов" << std::endl;
  std::cout << "3 - Показать список папок" << std::endl;
  std::cout << "4 - Показать Профиль пользователя" << std::endl;
  std::cout << "0 - Выйти в предыдущее меню" << std::endl;

  while (true) {
    if (!(std::cin >> userChoice)) {
      std::cout << "Ошибка ввода. Попробуйте еще раз." << std::endl;
      std::cin.clear(); // сбрасываем флаг ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Очищаем буфер ввода
      continue;
    }

    if (userChoice < 0 && userChoice != 4) {
      std::cout << "Вы ввели неправильное число. Попробуйте еще раз."
                << std::endl;
      continue;
    }

    break;
  }
  switch (userChoice) {
  case 0: { // exit
    break;
  }
  case 1: { // создать новый чат
    break;
  }
  case 2: {
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  default:
    break;
  }
}