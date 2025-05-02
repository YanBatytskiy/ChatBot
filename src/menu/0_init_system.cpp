/**
 * @file code_init_system.cpp
 * @brief Инициализация тестовой системы ChatBot для проверки пользователей, чатов и сообщений.
 * @version 1.0
 * @date 2025
 */

#include "menu/0_init_system.h"
#include "chat/chat.h"
#include "exception/validation_exception.h"
#include "system/system_function.h"

#include "message/message_content_struct.h"
#include "user/user.h"
#include "user/user_chat_list.h"

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Конструктор структуры InitDataArray.
 *
 * @param messageText Текст сообщения
 * @param timeStamp Временная метка сообщения
 * @param sender Отправитель сообщения
 * @param _recipients Список получателей сообщения
 */
InitDataArray::InitDataArray(std::string messageText, std::string timeStamp, std::shared_ptr<User> sender,
                             std::vector<std::shared_ptr<User>> _recipients)
    : _messageText(messageText), _timeStamp(timeStamp), _sender(sender), _recipients(_recipients) {}

/**
 * @brief Добавляет новое сообщение в чат на основе даннchatых InitDataArray.
 *
 * @param initDataArray Структура с данными для создания сообщения
 * @param chat Указатель на чат, куда добавляется сообщение
 */

/**
 * @brief Инициализация тестовой системы: создание пользователей, чатов и истории сообщений.
 *
 * @param _chatsystem Ссылка на объект системы чатов для заполнения тестовыми данными
 */
void systemInitTest(ChatSystem &_chatsystem) {
  // Создание пользователей
  auto Alex2104_ptr = std::make_shared<User>("a", "Sasha", "1");
  auto Elena1510_ptr = std::make_shared<User>("e", "Elena", "1");
  auto Serg0101_ptr = std::make_shared<User>("s", "Sergei", "1");
  auto Vit2504_ptr = std::make_shared<User>("v", "Vitaliy", "1");
  auto q_ptr = std::make_shared<User>("q", "q", "1");
  auto s_ptr = std::make_shared<User>("s", "s", "1");
  auto d_ptr = std::make_shared<User>("d", "d", "1");
  auto f_ptr = std::make_shared<User>("f", "f", "1");

  Alex2104_ptr->showUserData();
  Elena1510_ptr->showUserData();
  Serg0101_ptr->showUserData();
  Vit2504_ptr->showUserData();
  q_ptr->showUserData();
  s_ptr->showUserData();
  d_ptr->showUserData();
  f_ptr->showUserData();

  // Добавление пользователей в систему
  _chatsystem.addUser(Alex2104_ptr);
  _chatsystem.addUser(Elena1510_ptr);
  _chatsystem.addUser(Serg0101_ptr);
  _chatsystem.addUser(Vit2504_ptr);
  _chatsystem.addUser(q_ptr);
  _chatsystem.addUser(s_ptr);
  _chatsystem.addUser(d_ptr);
  _chatsystem.addUser(f_ptr);

  // Создание списков чатов для пользователей
  auto Alex2104_ChatList_ptr = std::make_shared<UserChatList>(Alex2104_ptr);
  auto Elena1510_ChatList_ptr = std::make_shared<UserChatList>(Elena1510_ptr);
  auto Serg0101_ChatList_ptr = std::make_shared<UserChatList>(Serg0101_ptr);
  auto Vit2504_ChatList_ptr = std::make_shared<UserChatList>(Vit2504_ptr);
  auto q_ChatList_ptr = std::make_shared<UserChatList>(q_ptr);
  auto s_ChatList_ptr = std::make_shared<UserChatList>(s_ptr);
  auto d_ChatList_ptr = std::make_shared<UserChatList>(d_ptr);
  auto f_ChatList_ptr = std::make_shared<UserChatList>(f_ptr);

  Alex2104_ptr->createChatList(Alex2104_ChatList_ptr);
  Elena1510_ptr->createChatList(Elena1510_ChatList_ptr);
  Serg0101_ptr->createChatList(Serg0101_ChatList_ptr);
  Vit2504_ptr->createChatList(Vit2504_ChatList_ptr);
  q_ptr->createChatList(q_ChatList_ptr);
  s_ptr->createChatList(s_ChatList_ptr);
  d_ptr->createChatList(d_ChatList_ptr);
  f_ptr->createChatList(f_ChatList_ptr);

  // Создание первого чата: Sasha и Elena (один на один)
  std::vector<std::shared_ptr<User>> recipients;
  std::vector<std::weak_ptr<User>> participants;

  recipients.push_back(Alex2104_ptr);
  participants.push_back(Elena1510_ptr);
  participants.push_back(Alex2104_ptr);

  auto chat_ptr = std::make_shared<Chat>();
  chat_ptr->addParticipant(Elena1510_ptr);
  chat_ptr->addParticipant(Alex2104_ptr);

  for (const auto &chatUser : participants) {
    try {
      if (auto chatUser_ptr = chatUser.lock()) {

        // добавление чата в чат-лист
        auto chatList = chatUser_ptr->getUserChatList();
        if (chatList) {
          chatList->addChat(chat_ptr);
        } else
          throw UnknownException("У пользователя нет списка чатов! init_system.");
      } else
        throw UnknownException("weak_ptr пустой. init_system.");
    } catch (const ValidationException &ex) {
      std::cout << " ! " << ex.what() << std::endl;
      return;
    }
  }

  _chatsystem.addChat(chat_ptr);

  InitDataArray Elena_Alex1("Привет", "01-04-2025,12:00:00", Elena1510_ptr, recipients);
  addMessageToChat(Elena_Alex1, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);

  InitDataArray Elena_Alex2("Хай! как делишки?", "01-04-2025,12:05:00", Alex2104_ptr, recipients);
  addMessageToChat(Elena_Alex2, chat_ptr);

  recipients.clear();
  recipients.push_back(Alex2104_ptr);

  InitDataArray Elena_Alex3("Хорошо, как насчет кофе?", "01-04-2025,12:07:00", Elena1510_ptr, recipients);
  addMessageToChat(Elena_Alex3, chat_ptr);

  changeLastReadIndexForSender(Elena1510_ptr, chat_ptr);

  chat_ptr->printChat(Elena1510_ptr);

  // Создание второго чата: Elena, Sasha и Сергей (групповой чат)
  chat_ptr.reset();
  recipients.clear();
  participants.clear();

  recipients.push_back(Alex2104_ptr);
  recipients.push_back(Serg0101_ptr);
  recipients.push_back(q_ptr);
  recipients.push_back(f_ptr);
  participants.push_back(Elena1510_ptr);
  participants.push_back(Alex2104_ptr);
  participants.push_back(Serg0101_ptr);
  participants.push_back(q_ptr);
  participants.push_back(f_ptr);

  chat_ptr = std::make_shared<Chat>();
  chat_ptr->addParticipant(Elena1510_ptr);
  chat_ptr->addParticipant(Alex2104_ptr);
  chat_ptr->addParticipant(Serg0101_ptr);
  chat_ptr->addParticipant(q_ptr);
  chat_ptr->addParticipant(f_ptr);

  for (const auto &chatUser : participants) {
    if (auto chatUser_ptr = chatUser.lock()) {
      auto chatList = chatUser_ptr->getUserChatList();
      if (chatList) {
        chatList->addChat(chat_ptr);

      } else {
        std::cout << "[Ошибка] У пользователя нет списка чатов!\n" << std::endl;
      }
    }
  }
  _chatsystem.addChat(chat_ptr);

  InitDataArray Elena_Alex_Serg1("Всем Привееет!?", "01-04-2025,13:00:00", Elena1510_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg1, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);
  recipients.push_back(Serg0101_ptr);
  recipients.push_back(q_ptr);
  recipients.push_back(f_ptr);

  InitDataArray Elena_Alex_Serg2("И тебе не хворать!?", "01-04-2025,13:02:00", Alex2104_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg2, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);
  recipients.push_back(Alex2104_ptr);
  recipients.push_back(q_ptr);
  recipients.push_back(f_ptr);

  InitDataArray Elena_Alex_Serg3("Тоже всем здрассьте.", "01-04-2025,13:10:15", Serg0101_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg3, chat_ptr);

  recipients.clear();
  recipients.push_back(Serg0101_ptr);
  recipients.push_back(Alex2104_ptr);
  recipients.push_back(q_ptr);
  recipients.push_back(f_ptr);

  InitDataArray Elena_Alex_Serg4("Куда идем?", "01-04-2025,13:12:09", Elena1510_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg4, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);
  recipients.push_back(Alex2104_ptr);
  recipients.push_back(q_ptr);
  recipients.push_back(f_ptr);

  InitDataArray Elena_Alex_Serg5("В кино!", "01-04-2025,13:33:00", Serg0101_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg5, chat_ptr);

  chat_ptr->updateLastReadMessageIndex(Elena1510_ptr, chat_ptr->getMessages().size() - 1);
  //   changeLastReadIndexForSender(Elena1510_ptr, chat_ptr);

  chat_ptr->printChat(Elena1510_ptr);
}