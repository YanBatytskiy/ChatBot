/**
 * @file auth_menu.h
 * @brief Заголовочный файл, содержащий объявления функций запуска системы и
 * авторизации.
 *
 * Используется в основном интерфейсе ChatBot для отображения меню входа и
 * регистрации.
 */

#pragma once
#include "system/chat_system.h"

/**
 * @brief Отображает главное меню авторизации и получает выбор пользователя.
 *
 * Функция выводит текстовое меню в консоль, обрабатывает ввод пользователя
 * и возвращает соответствующий код действия.
 *
 * @return short Значение, соответствующее выбору пользователя:
 * - 1 — Регистрация пользователя
 * - 2 — Вход в Чат
 * - 0 — Завершение программы
 */
short authMenu(); // вывод главного меню

/**
 * @brief Отображает главное меню авторизации и получает выбор пользователя.
 *
 * Функция выводит текстовое меню в консоль, обрабатывает ввод пользователя
 * и возвращает соответствующий код действия.
 *
 * @return short Значение, соответствующее выбору пользователя:
 * - 1 — Регистрация пользователя
 * - 2 — Вход в Чат
 * - 0 — Завершение программы
 */
short mainMenuChoice(ChatSystem &chatSystem); // вывод главного меню

void mainMenuList2(ChatSystem &chatSystem);

void menuListOpenChat1(ChatSystem &chatSystem, const std::shared_ptr<Chat> &chat, std::size_t Index);

void menuListFindChat2(ChatSystem &chatSystem);

void inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat, std::size_t unReadCountIndex);