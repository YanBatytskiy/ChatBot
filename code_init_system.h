/**
 * @file code_init_system.h
 * @brief Заголовочный файл для автоматической инициализации тестовой системы чатов и сообщений.
 *
 * Содержит структуру данных для описания сообщений и функции для создания тестовых пользователей,
 * чатов и сообщений в системе ChatBot.
 */

 #pragma once

 #include "chat_system.h"
 #include <memory>
 #include <string>
 #include <vector>
 
 /**
  * @brief Структура для хранения данных одного сообщения при автоматической генерации истории чата.
  */
 struct InitDataArray {
   std::string _messageText;               ///< Текст сообщения
   std::string _timeStamp;                  ///< Временная метка сообщения
   std::shared_ptr<User> _sender;            ///< Отправитель сообщения
   std::vector<std::shared_ptr<User>> _recipients; ///< Список получателей сообщения
 
   /**
	* @brief Конструктор InitDataArray.
	* 
	* @param messageText Текст сообщения
	* @param timeStamp Временная метка
	* @param sender Отправитель сообщения
	* @param _recipients Получатели сообщения
	*/
   InitDataArray(std::string messageText, std::string timeStamp,
				 std::shared_ptr<User> sender,
				 std::vector<std::shared_ptr<User>> _recipients);
 
   /// @brief Деструктор по умолчанию.
   virtual ~InitDataArray() = default;
 };

 void changeLastReadIndexForSender(const std::shared_ptr<User> &user, const std::shared_ptr<Chat> &chat);
 
 /**
  * @brief Создаёт сообщение на основе данных и добавляет его в указанный чат.
  *
  * @param initDataArray Структура с данными сообщения
  * @param chat Указатель на чат, куда будет добавлено сообщение
  */
 void addMessageToChat(const InitDataArray &initDataArray, std::shared_ptr<Chat> &chat);
 
 /**
  * @brief Инициализирует тестовую систему: создаёт пользователей, чаты и сообщения.
  *
  * @param _chatsystem Система чатов для заполнения тестовыми данными
  */
 void systemInitTest(ChatSystem &_chatsystem);
 