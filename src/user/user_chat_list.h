/**
 * @file user_chat_list.h
 * @brief Заголовочный файл с описанием класса UserChatList для системы ChatBot.
 *
 * Класс UserChatList хранит список чатов, в которых участвует пользователь,
 * и индексы последних прочитанных сообщений в каждом чате.
 */

#pragma once

#include "chat/chat.h"
#include <memory>
#include <vector>

class User;

/**
 * @brief Класс для хранения списка чатов пользователя и состояния их прочтения.
 */
class UserChatList {
private:
  std::weak_ptr<User> _owner;                 ///< Владелец списка чатов (пользователь)
  std::vector<std::weak_ptr<Chat>> _chatList; ///< Список чатов пользователя
  std::vector<std::size_t> _lastReadIndex;    ///< Номера последних прочитанных сообщений для каждого чата
  std::size_t _chatCount;

public:
  /**
   * @brief Конструктор списка чатов пользователя.
   *
   * @param owner Указатель на пользователя-владельца
   */
  UserChatList(const std::shared_ptr<User> &owner);

  /// @brief Деструктор по умолчанию.
  ~UserChatList() = default;

  // --- Геттеры ---
  std::size_t getChatCount() const;

  /**
   * @brief Получить владельца списка чатов.
   * @return Указатель на пользователя-владельца
   */
  std::weak_ptr<User> getOwner() const;

  /**
   * @brief Получить список чатов пользователя.
   * @return Вектор слабых указателей на чаты
   */
  std::vector<std::weak_ptr<Chat>> getChatFromList() const;

  /**
   * @brief Получить список последних прочитанных индексов сообщений по каждому чату.
   * @return Вектор индексов
   */
  std::vector<std::size_t> getLastReadIndex() const;

  // --- Сеттеры ---

  /**
   * @brief Добавить чат в список пользователя.
   *
   * @param chat Указатель на чат
   */
  void setChatCount(std::size_t chatCount);

  void addChat(const std::weak_ptr<Chat> &chat);

  void setLastReadIndex(std::size_t index, std::size_t value);

  // --- Дополнительные методы ---

  /**
   * @brief Отметить все сообщения во всех чатах как прочитанные.
   */
  void makeAllRead();
};
