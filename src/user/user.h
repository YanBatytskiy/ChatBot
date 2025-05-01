/**
 * @file user.h
 * @brief Заголовочный файл с описанием класса User для системы ChatBot.
 *
 * Класс User хранит информацию о пользователе, его логине, пароле,
 * отображаемом имени и списке чатов пользователя.
 */

#pragma once

#include <memory>
#include <string>

class UserChatList;

/**
 * @brief Класс, представляющий пользователя в системе чатов.
 */
class User {
private:
  std::string _login;                       ///< Логин пользователя
  std::string _userName;                    ///< Отображаемое имя пользователя
  std::string _password;                    ///< Пароль пользователя
  std::shared_ptr<UserChatList> _userChats; ///< Список чатов пользователя

public:
  /**
   * @brief Конструктор пользователя.
   *
   * @param login Логин пользователя
   * @param userName Имя пользователя для отображения
   * @param password Пароль пользователя
   */
  User(const std::string &login, const std::string &userName, const std::string &password);

  /// @brief Деструктор пользователя по умолчанию.
  ~User() = default;

  /**
   * @brief Связывает пользователя со списком его чатов.
   *
   * @param chats Указатель на объект списка чатов
   */
  void createChatList(const std::shared_ptr<UserChatList> &chats);

  // --- Геттеры ---

  /**
   * @brief Получить логин пользователя..addChat(chat_ptr)
   * @return Логин
   */
  std::string getLogin() const;

  /**
   * @brief Получить отображаемое имя пользователя.
   * @return Имя пользователя
   */
  std::string getUserName() const;

  /**
   * @brief Получить пароль пользователя.
   * @return Пароль
   */
  std::string getPassword() const;

  /**
   * @brief Получить список чатов пользователя.
   * @return Указатель на список чатов
   */
  std::shared_ptr<UserChatList> getUserChatList() const;

  // --- Сеттеры ---

  /**
   * @brief Установить новый логин пользователя.
   * @param login Новый логин
   */
  void setLogin(const std::string &login);

  /**
   * @brief Установить новое имя пользователя.
   * @param userName Новое имя
   */
  void setUserName(const std::string &userName);

  /**
   * @brief Установить новый пароль пользователя.
   * @param password Новый пароль
   */
  void setPassword(const std::string &password);

  // --- Дополнительные методы ---

  /**
   * @brief Проверяет соответствие пароля.
   * @param password Введённый пароль
   * @return true если пароль совпадает
   */
  bool checkPassword(const std::string &password) const;

  /**
   * @brief Проверяет соответствие логина.
   * @param login Введённый логин
   * @return true если логин совпадает
   */
  bool checkLogin(const std::string &login) const;

  /**
   * @brief Выводит информацию о пользователе.
   */
  void showUserData() const;

  /**
   * @brief Печатает список чатов пользователя.
   *
   * @param user Ссылка на пользователя, для которого печатается список чатов
   */
  void printChatList(const std::shared_ptr<User> &user) const;


  };
