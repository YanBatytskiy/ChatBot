/**
 * @file code_auth_menu.cpp
 * @brief Реализация начального меню авторизации ChatBot 'Shark'
 * @version 1.0
 * @date 2025
 */
#include "code_auth_menu.h"
#include <iostream>
#include <limits>

/**
 * @brief Инициализирует и запускает систему ChatBot.
 *
 * Пока функция пуста, но предусмотрена для дальнейшей инициализации системы.
 */
void StartSystem() { /// @brief start system
  ;
}

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
short authMenu() { // вывод главного меню
  std::cout << "ChatBot 'Shark' Версия 1.0. @2025 \n \n";
  short userChoice;

  std::cout << "Выберите пункт меню: \n1 - Регистрация пользователя \n2 - "
               "Войти в ЧатБот \n0 - Завершить программу"
            << std::endl;

  while (true) {
    if (!(std::cin >> userChoice)) {
      std::cout << "Ошибка ввода. Попробуйте еще раз." << std::endl;
      std::cin.clear(); // сбрасываем флаг ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Очищаем буфер ввода
      continue;
    }

    if (userChoice == 0) {
      std::cout << "До свидания!" << std::endl << std::endl;
      break;
    } else if (userChoice != 1 && userChoice != 2) {
      std::cout << "Вы ввели неправильное число. Попробуйте еще раз."
                << std::endl;
      continue;
    }

    break;
  }
  return userChoice;
}