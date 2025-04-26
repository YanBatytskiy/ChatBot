/**
 * @file code_init_system.cpp
 * @brief Инициализация тестовой системы ChatBot для проверки пользователей, чатов и сообщений.
 * @version 1.0
 * @date 2025
 */

#include "menu/code_init_system.h"
#include "chat/chat.h"
#include "message/message.h"
#include "message/message_content.h"
#include "message/message_content_struct.h"
#include "user/user.h"
#include "user/user_chat_list.h"

#include <algorithm>
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

void changeLastReadIndexForSender(const std::shared_ptr<User> &user, const std::shared_ptr<Chat> &chat) {
  // у нас есть chat и есть слабая ссылка на юзера
  // значит нам нужна из нее shared ссылка на юзера
  // чтобы потом получить чатлист и добавить в вектор индексов прочитанных сообщений новое значение для отправителя

  // зная юзера я могу взять shared ссылку на чатлист юзера
  auto userChatList_ptr = user->getUserChatList();
  auto chatList = userChatList_ptr->getChatFromList();

  if (!userChatList_ptr) {
    std::cerr << "[Ошибка] У пользователя нет списка чатов." << std::endl;
    return;
  }

  // далее я могу найти индекс чата в чат листе
  auto it = std::find_if(chatList.begin(), chatList.end(), [&chat](const std::weak_ptr<Chat> &weakp_ptr) {
    auto chat_ptr = weakp_ptr.lock();

    if ((!chat_ptr)) {
      return false;
    }
    return chat_ptr == chat;
  });

  // ищем индекс чата в чатлисте
  if (it != chatList.end()) {

    std::size_t index = std::distance(chatList.begin(), it);

    userChatList_ptr->setLastReadIndex(index, userChatList_ptr->getLastReadIndex()[index] + 1);
  } else {
    std::cerr << "[Ошибка] Чат не найден в списке пользователя." << std::endl;
  }
}

void addMessageToChat(const InitDataArray &initDataArray, std::shared_ptr<Chat> &chat) {

  std::vector<std::shared_ptr<IMessageContent>> iMessageContent;
  TextContent textContent(initDataArray._messageText);
  MessageContent<TextContent> messageContentText(textContent);
  iMessageContent.push_back(std::make_shared<MessageContent<TextContent>>(messageContentText));

  if (!initDataArray._sender) {
    std::cerr << "[Ошибка] Отправитель отсутствует. Сообщение не будет создано.\n" << std::endl;
  } else {
    Message message(iMessageContent, initDataArray._sender, initDataArray._timeStamp);

    chat->addMessage(std::make_shared<Message>(message));

    changeLastReadIndexForSender(initDataArray._sender, chat);
  };
}

/**
 * @brief Инициализация тестовой системы: создание пользователей, чатов и истории сообщений.
 *
 * @param _chatsystem Ссылка на объект системы чатов для заполнения тестовыми данными
 */
void systemInitTest(ChatSystem &_chatsystem) {
  // Создание пользователей
  auto Alex2104_ptr = std::make_shared<User>("Alex2104", "Sasha", "12345");
  auto Elena1510_ptr = std::make_shared<User>("Elena1510", "Elena", "12345");
  auto Serg0101_ptr = std::make_shared<User>("Serg0101", "Sergei", "12345");
  auto Vit2504_ptr = std::make_shared<User>("Vit2504", "Vitaliy", "12345");

  Alex2104_ptr->showUserData();
  Elena1510_ptr->showUserData();
  Serg0101_ptr->showUserData();
  Vit2504_ptr->showUserData();

  // Добавление пользователей в систему
  _chatsystem.addUser(Alex2104_ptr);
  _chatsystem.addUser(Elena1510_ptr);
  _chatsystem.addUser(Serg0101_ptr);
  _chatsystem.addUser(Vit2504_ptr);

  // Создание списков чатов для пользователей
  auto Alex2104_ChatList_ptr = std::make_shared<UserChatList>(Alex2104_ptr);
  auto Elena1510_ChatList_ptr = std::make_shared<UserChatList>(Elena1510_ptr);
  auto Serg0101_ChatList_ptr = std::make_shared<UserChatList>(Serg0101_ptr);
  auto Vit2504_ChatList_ptr = std::make_shared<UserChatList>(Vit2504_ptr);

  Alex2104_ptr->createChatList(Alex2104_ChatList_ptr);
  Elena1510_ptr->createChatList(Elena1510_ChatList_ptr);
  Serg0101_ptr->createChatList(Serg0101_ChatList_ptr);
  Vit2504_ptr->createChatList(Vit2504_ChatList_ptr);

  // Создание первого чата: Sasha и Elena (один на один)
  std::vector<std::shared_ptr<User>> recipients;
  std::vector<std::weak_ptr<User>> participients;

  recipients.push_back(Alex2104_ptr);
  participients.push_back(Elena1510_ptr);
  participients.push_back(Alex2104_ptr);

  auto chat_ptr = std::make_shared<Chat>(participients);

  for (const auto &chatUser : participients) {
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

  Elena1510_ChatList_ptr->setLastReadIndex(0, 3);

  chat_ptr->printChat(Elena1510_ptr);

  // Создание второго чата: Elena, Sasha и Сергей (групповой чат)
  chat_ptr.reset();
  recipients.clear();
  participients.clear();

  recipients.push_back(Alex2104_ptr);
  recipients.push_back(Serg0101_ptr);
  participients.push_back(Elena1510_ptr);
  participients.push_back(Alex2104_ptr);
  participients.push_back(Serg0101_ptr);

  chat_ptr = std::make_shared<Chat>(participients);

  for (const auto &chatUser : participients) {
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

  InitDataArray Elena_Alex_Serg2("И тебе не хворать!?", "01-04-2025,13:02:00", Alex2104_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg2, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);
  recipients.push_back(Alex2104_ptr);

  InitDataArray Elena_Alex_Serg3("Тоже всем здрассьте.", "01-04-2025,13:10:15", Serg0101_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg3, chat_ptr);

  recipients.clear();
  recipients.push_back(Serg0101_ptr);
  recipients.push_back(Alex2104_ptr);

  InitDataArray Elena_Alex_Serg4("Куда идем?", "01-04-2025,13:12:09", Elena1510_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg4, chat_ptr);

  recipients.clear();
  recipients.push_back(Elena1510_ptr);
  recipients.push_back(Alex2104_ptr);

  InitDataArray Elena_Alex_Serg5("В кино!", "01-04-2025,13:33:00", Serg0101_ptr, recipients);
  addMessageToChat(Elena_Alex_Serg5, chat_ptr);

  Elena1510_ChatList_ptr->setLastReadIndex(1, 4);

  chat_ptr->printChat(Elena1510_ptr);
}
