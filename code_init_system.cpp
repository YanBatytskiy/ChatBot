#include "code_init_system.h"
#include "chat.h"
#include "message.h"
#include "message_content.h"
#include "message_content_struct.h"
#include "user.h"
#include "user_chat_list.h"

#include <iostream>
#include <memory>
#include <vector>

InitDataArray::InitDataArray(std::string messageText, std::string timeStamp, std::shared_ptr<User> sender,
                             std::vector<std::shared_ptr<User>> _recipients)
    : _messageText(messageText), _timeStamp(timeStamp), _sender(sender), _recipients(_recipients) {}

void systemInitTest(ChatSystem &_chatsystem) {

  // проверка системы сообщений
  // создаем умный указатель на пользователей
  auto Alex2104_ptr = std::make_shared<User>("Alex2104", "Sasha", "12345");
  auto Elena1510_ptr = std::make_shared<User>("Elena1510", "Elena", "12345");
  auto Serg0101_ptr = std::make_shared<User>("Serg0101", "Sergei", "12345");
  auto Vit2504_ptr = std::make_shared<User>("Vit 2504", "Vitaliy", "12345");

  Alex2104_ptr->showUserData();
  Elena1510_ptr->showUserData();
  Serg0101_ptr->showUserData();
  Vit2504_ptr->showUserData();

  // добавляем пользователей в систему
  _chatsystem.addUser(Alex2104_ptr);
  _chatsystem.addUser(Elena1510_ptr);
  _chatsystem.addUser(Serg0101_ptr);
  _chatsystem.addUser(Vit2504_ptr);

  // создаем список чатов UserChatList для каждого
  // пользователя. Мы создвем и привязываем список
  // чатов при регистрации пользователя
  std::shared_ptr<UserChatList> Alex2104_ChatList_ptr = std::make_shared<UserChatList>(Alex2104_ptr);
  std::shared_ptr<UserChatList> Elena1510_ChatList_ptr = std::make_shared<UserChatList>(Elena1510_ptr);
  std::shared_ptr<UserChatList> Serg0101_ChatList_ptr = std::make_shared<UserChatList>(Serg0101_ptr);
  std::shared_ptr<UserChatList> Vit2504_ChatList_ptr = std::make_shared<UserChatList>(Vit2504_ptr);

  // привязываем список чатов к юзеру
  Alex2104_ptr->createChatList(Alex2104_ChatList_ptr);
  Elena1510_ptr->createChatList(Elena1510_ChatList_ptr);
  Serg0101_ptr->createChatList(Serg0101_ChatList_ptr);
  Vit2504_ptr->createChatList(Vit2504_ChatList_ptr);

  /*
   *
   *
   *
   *
   */

  // создаем историю сообщений
  // Sasha - Elena - чат Один с Одним

  std::vector<std::shared_ptr<User>> recipients;
  std::vector<std::weak_ptr<User>> participients;

  auto chat_ptr1 = std::make_shared<Chat>(participients);

  recipients.push_back(Alex2104_ptr);
  participients.push_back(Elena1510_ptr);
  participients.push_back(Alex2104_ptr);

  InitDataArray Elena_Alex1("Привет", "01-04-2025,12:00:00", Elena1510_ptr, recipients);

  // создаем вектор из MessangeContent для включения в Message
  std::vector<std::shared_ptr<IMessageContent>> iMessageContent;
  // создаем переменную структуры TextContent
  TextContent textContent(Elena_Alex1._messageText);
  // создаем объкт для включения в сообщение
  MessageContent<TextContent> messageContentText(textContent);
  // создаем указатель на него
  std::shared_ptr<IMessageContent> messageContentText_ptr = std::make_shared<MessageContent<TextContent>>(
      messageContentText);
  // и добавляем его в вектор MessageContent
  iMessageContent.push_back(messageContentText_ptr);
  // создаем объект Message
  Message message(iMessageContent, Elena1510_ptr, Elena_Alex1._timeStamp);
  // добавляем Message в Chat
  chat_ptr1->addMessage(std::make_shared<Message>(message));
  // добавляем чат в список чатов каждого пользователя

  for (const auto &chatUser : participients) {
    if (auto chatUser_ptr = chatUser.lock()) {
      chatUser_ptr->getUserChatList()->addChat(chat_ptr1);
    } else {
      std::cout << "user уничтожен " << chatUser_ptr->getLogin() << std::endl;
    }
  }

  recipients.clear();
  participients.clear();
  iMessageContent.clear();
  messageContentText_ptr.reset();

//   message.printMessage(Elena1510_ptr);

  auto chat_ptr2 = std::make_shared<Chat>(participients);

  recipients.push_back(Elena1510_ptr);
  participients.push_back(Alex2104_ptr);
  participients.push_back(Elena1510_ptr);

  InitDataArray Elena_Alex2("Хай! как делишки?", "01-04-2025,12:05:00", Alex2104_ptr, recipients);
  // создаем вектор из MessangeContent для включения в Message
  //   std::vector<std::shared_ptr<IMessageContent>> iMessageContent;
  // создаем переменную структуры TextContent
  TextContent textContent2(Elena_Alex2._messageText);
  // создаем объкт для включения в сообщение
  MessageContent<TextContent> messageContentText2(textContent2);
  // создаем указатель на него
  std::shared_ptr<IMessageContent> messageContentText2_ptr = std::make_shared<MessageContent<TextContent>>(
      messageContentText2);
  // и добавляем его в вектор MessageContent
  iMessageContent.push_back(messageContentText2_ptr);
  // создаем объект Message
  Message message2(iMessageContent, Elena1510_ptr, Elena_Alex1._timeStamp);
  // добавляем Message в Chat
  chat_ptr2->addMessage(std::make_shared<Message>(message2));
  // добавляем чат в список чатов каждого пользователя

  for (const auto &chatUser : participients) {
    if (auto chatUser_ptr = chatUser.lock()) {
      chatUser_ptr->getUserChatList()->addChat(chat_ptr2);
    } else {
      std::cout << "user уничтожен " << chatUser_ptr->getLogin() << std::endl;
    }
  }

  chat_ptr2->printChat(Elena1510_ptr);

  // recipients.clear();
  //   recipients.push_back(Alex2104_ptr);
  //   InitDataArray Elena_Alex3("Хорошо, как насчет кофе?", "01-04-2025,12:07:00", Elena1510_ptr, recipients);
};