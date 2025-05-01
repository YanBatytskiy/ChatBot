/**
 * @file user.cpp
 * @brief Реализация методов класса User для системы ChatBot.
 * @version 1.0
 * @date 2025
 */

#include "user/user.h"
#include "user/user_chat_list.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>

// --- Конструкторы ---

/**
 * @brief Конструктор класса User.
 *
 * @param login Логин пользователя
 * @param userName Имя пользователя для отображения
 * @param password Пароль пользователя
 */
User::User(const std::string &login, const std::string &userName, const std::string &password)
    : _login(login), _userName(userName), _password(password) {}

/**
 * @brief Создание списка чатов для пользователя.
 *
 * @param userChats Указатель на объект списка чатов
 */
void User::createChatList(const std::shared_ptr<UserChatList> &userChats) { _userChats = userChats; }

// --- Геттеры ---

/**
 * @brief Получение логина пользователя.
 * @return Логин пользователя
 */
std::string User::getLogin() const { return _login; }

/**
 * @brief Получение имени пользователя.
 * @return Имя пользователя
 */
std::string User::getUserName() const { return _userName; }

/**
 * @brief Получение пароля пользователя.
 * @return Пароль пользователя
 */
std::string User::getPassword() const { return _password; }

/**
 * @brief Получение списка чатов пользователя.
 * @return Указатель на объект списка чатов
 */
std::shared_ptr<UserChatList> User::getUserChatList() const { return _userChats; }

// --- Сеттеры ---

/**
 * @brief Установка нового логина пользователя.
 * @param login Новый логин
 */
void User::setLogin(const std::string &login) { _login = login; }

/**
 * @brief Установка нового имени пользователя.
 * @param userName Новое имя
 */
void User::setUserName(const std::string &userName) { _userName = userName; }

/**
 * @brief Установка нового пароля пользователя.
 * @param password Новый пароль
 */
void User::setPassword(const std::string &password) { _password = password; }

// --- Дополнительные методы ---

/**
 * @brief Проверка корректности пароля.
 *
 * @param password Пароль для проверки
 * @return true, если пароль совпадает
 */
bool User::checkPassword(const std::string &password) const { return (password == _password); }

/**
 * @brief Проверка корректности логина.
 *
 * @param login Логин для проверки
 * @return true, если логин совпадает
 */
bool User::checkLogin(const std::string &login) const { return (_login == login); }

/**
 * @brief Вывод данных пользователя в консоль.
 */
void User::showUserData() const {
  std::cout << "Name: " << _userName << ", Login: " << _login << ", Password: " << _password << std::endl;
}

/**
 * @brief Печать списка чатов пользователя.
 *
 *
 *
 * @param user Ссылка на пользователя, для которого нужно напечатать список чатов
 */
void User::printChatList(const std::shared_ptr<User> &user) const {
  // ДОДЕЛАТЬ ВЫВОД УДАЛЕННОГО ПОЛЬЗОВАТЕЛЯ В СПИСКЕ а также количество новых сообщений в списке

  // достаем чатлист
  const auto &chatList = user->getUserChatList()->getChatFromList();

  if (chatList.empty()) {
    std::cout << "У пользователя " << user->_userName << " нет чатов." << std::endl;
    return;
  }
  std::cout << std::endl
            << "Всего чатов = " << user->getUserChatList()->getChatCount() << ". Список чатов пользователя "
            << user->_userName << " :" << std::endl;

  std::size_t index = 1;
  std::size_t activeUserMessageCount;
  std::size_t totalMessages;

  // перебираем чаты в списке
  for (const auto &weakChat : chatList) {
	  if (auto chat_ptr = weakChat.lock()) {
		std::cout << std::endl;
		std::cout << index << ". ";
		totalMessages = chat_ptr->getMessages().size();
		
		// перебираем участников чата
		for (const auto &participient : chat_ptr->getParticipients()) {
			auto user_ptr = participient._user.lock();
			if (user_ptr) {
				if (user_ptr != user) {
					std::cout << user_ptr->getUserName() << "; ";
				} else {
					activeUserMessageCount = participient._lastReadMessageIndex;
				};
			} else {
				std::cout << "удал. пользоыватель";
			}
		}
    } else {
		//   std::cout << "Чат удален." << std::endl;
    }
    ++index;
	
    // вывод на печать количества новых сообщений
    if (totalMessages > activeUserMessageCount)
	std::cout << "новых сообщений - " << totalMessages - activeUserMessageCount;
}

std::cout << std::endl;
}
